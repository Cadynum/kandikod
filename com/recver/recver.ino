#include "com.h"
#include "state.h"

#define tty Serial
#define bt Serial1

void setup() {
	tty.begin(115200);
	bt.begin(115200);
}

Control ctl;

void loop() {
	boolean p = recv_bytes(&bt, (byte*)&ctl, sizeof(ctl));
	if (p) {
		tty.print("Mottagit: ");
		ctl.print(&tty);
	}
	delay(10);
}
