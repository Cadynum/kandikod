#include <math.h>
#include <Servo.h>

#include "com.h"
#include "state.h"
#include "butterworth.h"
#include "angletodistance.h"
#include "kraft.h"
#include "constants.h"
#include "object.h"


//Pin definitioner
#define tty Serial
#define bt Serial1
const int pin_servo[] = {2,3,4,5,6,7};
const int pin_pressure[] = {A0, A1, A2};

const byte led_table[] =
	{ B00000000
	, B10000000
	, B11000000
	, B11100000
	, B11110000
	, B11111000
	, B11111100
	, B11111110
	, B11111111
	, B01111111
	, B00111111
	, B00011111
	, B00001111
	, B00000111
	, B00000011
	, B00000001
	, B01010101
};
const unsigned led_table_len = sizeof(led_table);

Servo servo[SENSORS];
Control ctl;
RobotHand rh;

float force[FINGERS];


// Trycksensorer
bw_state bw[FINGERS];


void setup() {
	tty.begin(115200);
	bt.begin(115200);
	for (unsigned int i=0; i<SENSORS; i++) {
		servo[i].attach(pin_servo[i]);
	}
}

bool half = false;
void loop_real() {
	// benchmark();
	for (unsigned i=0; i < FINGERS; i++) {
		unsigned volt = butterworth(bw+i, analogRead(pin_pressure[i]));
		float newton = voltage_to_force[i][volt];

		tty.print(volt);
		tty.print(" ");
		// tty.print(newton);
		// tty.print(" ");
		rh.force[i] = led_table[
			min(led_table_len-1, (unsigned)(newton+0.5))
			];
		force[i] = newton;
		// tty.print(" ");
		// tty.print(rh.force[i]);
		// tty.print(' ');
	}

	Tuple tpl = getdistance(&ctl);
	tty.print(tpl.a);
	tty.print(' ');
	tty.println(tpl.b);


	//Send to controlglove
	if (half) {
		send_bytes(&bt, (byte*)&rh, sizeof(rh));
		// tty.print(sizeof(rh));
		// tty.print(' ');
		// tty.print(rh.force[0]);
		// tty.print(' ');
		// tty.print(rh.force[1]);
		// tty.print(' ');
		// tty.print(rh.force[2]);
		// tty.println();
	}
	half = !half;

	// Recieve from controlglove
	if (recv_bytes(&bt, (byte*)&ctl, sizeof(ctl))) {
		for(unsigned i = 0; i < SENSORS; i++) {
			servo[i].write(ctl.flex[i]);
		}
		// double maxforce = max(force[0], force[1]);
		// double dist = getdistance(&ctl);

		// if (!object_stop(dist, maxforce)) {
		// 	servo[0].write(ctl.flex[0]);
		// 	servo[1].write(ctl.flex[1]);
		// // }
		// servo[2].write(ctl.flex[2]);
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