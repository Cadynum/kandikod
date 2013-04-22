#include "com.h"

#define SYNC_LEN (sizeof(sync))
const byte sync[] = {0xFF, 'S', 'Y', 'N', 0xFF};


void send_bytes(HardwareSerial *s, const byte *buf, const unsigned int len) {
	s->write(sync, SYNC_LEN);
	s->write(buf, len);
}

// Not thread safe
boolean recv_bytes(HardwareSerial *s, byte *buf, const unsigned int len) {
	static unsigned int state = 0;
	static unsigned int cb = 0;

	while (s->available() > 0) {
		byte c = s->read();

		//Done with sync bits
		if (state == SYNC_LEN) {
			if (cb == len) {
				state = 0;
				cb = 0;
				return true;
			} else {
				buf[cb] = c;
				cb ++;
			}
		} else if (c == sync[state]) {
			state++;
		} else {
			state = 0;
		}
	}
	return false;
}