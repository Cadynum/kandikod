#include "com.h"
#include "state.h"

#define tty Serial
#define bt Serial1

const int cal_low = 3;
const int cal_high = 2;

const int pin_flex[] = {A0, A1, A2, A3, A4, A5};

unsigned int ref_low[SENSORS];
unsigned int ref_high[SENSORS];
Control ctl;



void setup() {
	tty.begin(115200);
	bt.begin(115200);
	pinMode(cal_low, INPUT);
	pinMode(cal_high, INPUT);
}

void printcal() {
	tty.print("CAL");
	for (unsigned int i=0; i<SENSORS; i++) {
		tty.print("(");
		tty.print(ref_low[i]);
		tty.print(", ");
		tty.print(ref_high[i]);
		tty.print(")  ");
	}
	tty.print("\r\n");
}

void loop() {
	if (digitalRead(cal_low)) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_low[i] = analogRead(pin_flex[i]);
		}
	}
	if (digitalRead(cal_high)) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_high[i] = analogRead(pin_flex[i]);
		}
	}

	for (unsigned int i=0; i<SENSORS; i++) {
		int val = analogRead(pin_flex[i]);
		val = constrain(val, ref_low[i], ref_high[i]);
		ctl.flex[i] = map(val
			, ref_low[i], ref_high[i]
			, 25, 159);
	}


	send_bytes(&bt, (byte*)&ctl, sizeof(ctl));
	printcal();
	delay(10);
	// // tty.println("Skickat ");
	// ctl.print(&tty);
	// delay(10);
}
