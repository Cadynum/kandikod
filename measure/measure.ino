// #include "butterworth.h"

#define tty Serial

#define SENSORS 6
const int pin_flex[] = {A0, A1, A2, A3, A4, A5};

// struct bw_state filter_s[SENSORS];



void setup() {
	tty.begin(115200);
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
		unsigned long now = micros();
		if (now < expect) {
		 	delayMicroseconds(expect - now);
		} else {
			tty.println(">> WARNING: FRAME UNDERRUN");
		}
	}
}

void loop_real() {
	for(unsigned i=0; i != SENSORS; i++) {
		unsigned val = analogRead(pin_flex[i]);
		tty.print(val);
		if (i != SENSORS-1)
			tty.print('\t');
	}
	tty.println();
}
