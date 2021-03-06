#include "com.h"
#include "state.h"
#include "butterworth.h"
#include "constants.h"

#define tty Serial
#define bt Serial1

#define DEBUG
#define LEDBAR 8

const int pin_flex[] = {A0, A1, A2, A3, A4, A5};
const int pin_cal_open = 5;
const int pin_cal_closed = 3;

const int led_clk = 12;
const int led_rst = 11;
const int led_data[] = {8,9,10};

const int open_bound[] = {110, 85, 155, 45, 30, 35};
const int closed_bound[] = {30, 27, 50, 150, 150, 150};


unsigned int ref_open[SENSORS];
unsigned int ref_closed[SENSORS];
struct bw_state filter_s[SENSORS];
Control ctl;
RobotHand rh, rh_old;



void setup() {
	pinMode(pin_cal_open, INPUT);
	pinMode(pin_cal_closed, INPUT);
	pinMode(led_clk, OUTPUT);
	pinMode(led_rst, OUTPUT);
	for(unsigned i=0; i != FINGERS; i++) {
		pinMode(led_data[i], OUTPUT);
	}
	digitalWrite(led_clk, 0);
	digitalWrite(led_rst, 0);
	digitalWrite(led_rst, 1);
	tty.begin(115200);
	bt.begin(115200);
}

void printcal() {
	tty.print("CAL");
	for (unsigned int i=0; i<SENSORS; i++) {
		tty.print("(");
		tty.print(ref_open[i]);
		tty.print(", ");
		tty.print(ref_closed[i]);
		tty.print(")  ");
	}
	tty.print("\r\n");
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
	// benchmark();
	int v1 = digitalRead(pin_cal_open);
	int v2 = digitalRead(pin_cal_closed);
	if (!v1) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_open[i] = analogRead(pin_flex[i]);
		}
		#ifdef DEBUG
		printcal();
		#endif
	} else if (!v2) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_closed[i] = analogRead(pin_flex[i]);
		}
		#ifdef DEBUG
		printcal();
		#endif
	}


	for (unsigned int i=0; i<SENSORS; i++) {
		unsigned int val = butterworth(filter_s+i, analogRead(pin_flex[i]));
		// int val = analogRead(pin_flex[i]);
		val = constrain(val, ref_open[i], ref_closed[i]);
		ctl.flex[i] = map(val
			, ref_open[i], ref_closed[i]
			, open_bound[i], closed_bound[i]);
	}

	send_bytes(&bt, (byte*)&ctl, sizeof(ctl));

	// Recieve force
	if (recv_bytes(&bt, (byte*)&rh, sizeof(rh)) && !(rh == rh_old)) {
		rh_old = rh;
		
		digitalWrite(led_rst, 0);
		digitalWrite(led_rst, 1);
		for(unsigned k=0; k != LEDBAR; k++) {
			//unrolled to optimize by reducing flicker
			digitalWrite(led_data[0], rh.force[0] & 1);
			digitalWrite(led_data[1], rh.force[1] & 1);
			digitalWrite(led_data[2], rh.force[2] & 1);
			rh.force[0] >>= 1;
			rh.force[1] >>= 1;
			rh.force[2] >>= 1;
			digitalWrite(led_clk, 1);
			digitalWrite(led_clk, 0);
		}
	}
}
