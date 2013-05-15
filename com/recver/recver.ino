#include <Servo.h>

#include "com.h"
#include "state.h"
#include "butterworth.h"

#define tty Serial
#define bt Serial1

const int pin_servo[] = {2,3,4,5,6,7};
const int pin_pressure[] = {A0, A1, A2};

Servo servo[SENSORS];
Control ctl;
RobotHand rh;

bw_state p_state;

unsigned int pressure[FINGERS];

void setup() {
	tty.begin(115200);
	bt.begin(115200);
	for (unsigned int i=0; i<SENSORS; i++) {
		servo[i].attach(pin_servo[i]);
	}
}


void loop_real() {
	benchmark();
	for (unsigned i=0; i < FINGERS; i++) {
		pressure[i] = analogRead(pin_pressure[i]);
		tty.print(pressure[i]);
		tty.print(" ");

	}
	tty.println();

	//Send to controlglove
	// send_bytes(&bt, (byte*)&rh, sizeof(rh));

	// Recieve from controlglove
	if (recv_bytes(&bt, (byte*)&ctl, sizeof(ctl))) {
		// tty.println("Mottaget: ");
		// ctl.print(&tty);
		for (unsigned int i=0; i<SENSORS; i++) {
			servo[i].write(ctl.flex[i]);
		}
	}
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
const unsigned long us_per_frame = 5000UL;
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