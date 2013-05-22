#include "butterworth.h"

#define tty Serial
#define bt Serial1



void setup() {
	tty.begin(115200);
}

void benchmark() {
	static unsigned long lasttime = 0;
	static unsigned int counter = 0;

	if (counter == 1000) {
		unsigned long now = millis();
		unsigned long diff = now - lasttime;
		counter = 0;
		lasttime = now;
		tty.print("FPS: ");
		tty.println((double)1000000/diff);
	} else {
		counter++;
	}
}

/* Assumes frames are always faster than 10000us. (which they are)
 * If they are not it will stop to work ~70min after power on.
 */
const unsigned long us_per_frame = 10000UL;
void loop() {
	unsigned long t_start = micros();
	unsigned long expect = t_start;

	for (;;) {
		expect += us_per_frame;
		loop_real();
		unsigned long now = millis();
		if (now < expect) {
		 	delayMicroseconds(expect - now);
		}
	}
}

bw_state apa = {0, 0};
void loop_real() {
	benchmark();
	unsigned int val = 1023 - analogRead(A2);
	unsigned int post = butterworth(&apa, val);
	tty.print(val);
	tty.print(" : ");
	// tty.print(apa.xp);
	// tty.print(" : ");
	// tty.print(apa.yp);
	// tty.print(" : ");
	tty.println(post);
}
