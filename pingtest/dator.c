#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

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

char msg[16];
#define LEN (sizeof(msg)-1)
char buff[32];

int main()
{
	timespec ts1, ts2, diff;
	int len, msglen;
	int fd = open("/dev/rfcomm1", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		perror("Open serial");
		return 1;
	}
	fcntl(fd, F_SETFL, 0);



	for (unsigned i=0; i < 100; i++) {
		msglen = sprintf(msg, "PING %u", i)-1;
		clock_gettime(CLOCK_REALTIME, &ts1);
		write(fd, msg, msglen);
		len = read(fd, buff, msglen);
		clock_gettime(CLOCK_REALTIME, &ts2);
	
		diff = getdiff(ts1, ts2);
		printf("sent: %d recvd: %d svar: %.*s diff: %ds %fms\n"
		,msglen, len, msglen, buff, diff.tv_sec, (double)diff.tv_nsec/1000000);
	}

	close(fd);
	return 0;
	
}
