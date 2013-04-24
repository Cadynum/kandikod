#include "com.h"

#define SYNC_LEN (sizeof(sync))
const byte sync[] = {0xFF, 'S', 'Y', 'N', 0xFF};
// const byte sync[] = {'S', 'Y', 'N'};


void send_bytes(HardwareSerial *s, const byte *buf, const unsigned int len) {
	s->write(sync, SYNC_LEN);
	s->write(buf, len);
}

// Not thread safe
boolean recv_bytes(HardwareSerial *s, byte *buf, const unsigned int len) {
	static unsigned int state = 0;
	static unsigned int cb = 0;

	while (s->available()) {
		byte c = s->read();

		//Done with sync bits
		if (state == SYNC_LEN) {
			buf[cb] = c;
			cb++;
			if (cb == len) {
				state = 0;
				cb = 0;
				return true;
			}
		} else if (c == sync[state]) {
			state++;
		} else if (c == sync[0]) {
			state = 1;
		} else {
			state = 0;
		}
	}
	return false;
}