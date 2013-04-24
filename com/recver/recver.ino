#include <Servo.h>

#include "com.h"
#include "state.h"


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


void loop() {
	while (tty.available()) {
		tty.read();
	}
	// while (bt.available()) {
	// 	tty.print(bt.read());
	// }

	if (recv_bytes(&bt, (byte*)&ctl, sizeof(ctl))) {
		// tty.print('x');
		// tty.println("Mottaget: ");
		// ctl.print(&tty);
		for (unsigned int i=0; i<SENSORS; i++) {
			servo[i].write(ctl.flex[i]);
		}
	}

	// delay(100);
}
