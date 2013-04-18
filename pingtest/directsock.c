#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

typedef struct timespec timespec;

timespec getdiff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

char inbuf[16];
char outbuf[16];

int main(int argc, char **argv)
{
	timespec ts1, ts2, diff;
	struct sockaddr_rc addr = { 0 };
	int s, status;
	char dest[18] = "00:06:66:4B:45:7A";

	// allocate a socket
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	// set the connection parameters (who to connect to)
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba( dest, &addr.rc_bdaddr );

	// connect to server
	status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	if (status == -1) {
		perror("connect");
		return 1;
	}

	const size_t measures = 100;
	size_t outbuf_len;
	unsigned i;
	double timearray[measures];
	for (i=0; i < measures; i++) {
		outbuf_len = sprintf(outbuf, "PING %u", i);

		clock_gettime(CLOCK_REALTIME, &ts1);

		if (write(s, outbuf, outbuf_len) == -1) {
			perror("send");
			return 1;
		}

		size_t accum = 0;
		do {
			int stat = read(s, inbuf+accum, outbuf_len-accum);
			if (stat == -1) {
				perror("recv fail");
				return 1;
			}
			accum += stat;
		} while ( accum < outbuf_len);

		clock_gettime(CLOCK_REALTIME, &ts2);
	
		diff = getdiff(ts1, ts2);
		double diff_ms = diff.tv_sec*1000 +(double)diff.tv_nsec/1000000;
		timearray[i] = diff_ms;
		printf("%.*s diff: %fms\n"
		, outbuf_len, inbuf, diff_ms);

	}
	double avg = 0, variance = 0, stddev = 0;
	for (int i=0; i<measures; i++) {
		avg += timearray[i];
	}
	avg /= measures;

	for (int i=0; i<measures; i++) {
		double tmp = timearray[i]-avg;
		variance += tmp*tmp;
	}
	variance /= measures;
	stddev = sqrt(variance);


	printf("Avg: %.1fms std.dev: %.1fms\n", avg, stddev);

	close(s);
	return 0;
}
