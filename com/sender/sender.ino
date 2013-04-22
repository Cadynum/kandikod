#include "com.h"
#include "state.h"

#define tty Serial
#define bt Serial1

void setup() {
	tty.begin(115200);
	bt.begin(115200);
}
Control ctl = {{10, 20, 30}, {40, 50, 60}};

void loop() {
	send_bytes(&bt, (byte*)&ctl, sizeof(ctl));
	tty.print("Skickat ");
	ctl.print(&tty);
	delay(1000);
}
