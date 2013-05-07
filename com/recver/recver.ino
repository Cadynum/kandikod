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

void setup() {
	tty.begin(115200);
	bt.begin(115200);
	for (unsigned int i=0; i<SENSORS; i++) {
		servo[i].attach(pin_servo[i]);
	}
}


void loop() {
	// while (tty.available()) {
	// 	tty.read();
	// }
	// while (bt.available()) {
	// 	tty.print(bt.read());
	// }
	// for(unsigned int i=0; i < FINGERS; i++) {
		
	// }
	
	tty.println(analogRead(A0));


	//Send to controlglove
	// send_bytes(&bt, (byte*)&rh, sizeof(rh));

	//Recieve from controlglove
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
