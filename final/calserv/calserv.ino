#include <Servo.h>

#include "com.h"
#include "state.h"
#include "angletodistance.h"


#define tty Serial
#define bt Serial1

const int pin_servo[] = {2,3,4,5,6,7};

Servo servo[SENSORS];
Control ctl;

void setup() {
	tty.begin(115200);
	bt.begin(115200);
	for (unsigned int i=0; i<SENSORS; i++) {
		servo[i].attach(pin_servo[i]);
	}
}

int s = -1;
int ang = -1;

void loop() {
	if (tty.available()) {
		s = tty.parseInt();
		ang = tty.parseInt();
	}
	if (s >= 0 && s < SENSORS) {
		servo[s].write(ang);
		ctl.flex[s] = ang;
		tty.print("Set servo ");
		tty.print(s);
		tty.print(" ang: ");
		tty.println(ang);
		while (tty.available()) {
			tty.read();
		}
		s = -1;
		ang = 0;
	}
	tty.println(getdistance(&ctl));

	// while (bt.available()) {
	// 	tty.print(bt.read());
	// }

	// if (recv_bytes(&bt, (byte*)&ctl, sizeof(ctl))) {
	// 	// tty.print('x');
	// 	// tty.println("Mottaget: ");
	// 	// ctl.print(&tty);
	// 	for (unsigned int i=0; i<SENSORS; i++) {
	// 		servo[i].write(ctl.flex[i]);
	// 	}
	// }

	// delay(100);
}
