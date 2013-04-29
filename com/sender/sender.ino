#include "com.h"
#include "state.h"

#define tty Serial
#define bt Serial1

const int cal_low = 5;
const int cal_high = 3;

const int pin_flex[] = {A0, A1, A2, A3, A4, A5};

const int low_bound[] = {50, 30, 159, 50, 30, 30};
const int high_bound[] = {98, 115, 90, 160, 120, 150};

unsigned int ref_low[SENSORS];
unsigned int ref_high[SENSORS];
Control ctl;



void setup() {
	pinMode(cal_low, INPUT);
	pinMode(cal_high, INPUT);
	tty.begin(115200);
	bt.begin(115200);
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
	int v1 = digitalRead(cal_low);
	int v2 = digitalRead(cal_high);
	if (!v1) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_low[i] = analogRead(pin_flex[i]);
		}
		// tty.println("LOcal");
	} else if (!v2) {
		for (unsigned int i=0; i<SENSORS; i++) {
			ref_high[i] = analogRead(pin_flex[i]);
		}
		// tty.println("HIcal");
	}
	// tty.print(v1);
	// tty.print(' ');
	// tty.println(v2);

	for (unsigned int i=0; i<SENSORS; i++) {
		int val = analogRead(pin_flex[i]);
		val = constrain(val, ref_low[i], ref_high[i]);
		ctl.flex[i] = map(val
			, ref_low[i], ref_high[i]
			, low_bound[i], high_bound[i]);
	}


	send_bytes(&bt, (byte*)&ctl, sizeof(ctl));
	printcal();
	delay(10);
	// // tty.println("Skickat ");
	// ctl.print(&tty);
	// delay(10);
}
