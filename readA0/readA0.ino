#define tty Serial


void setup() {
	tty.begin(115200);
}

int T = 10; //ms
unsigned long last = 0;

void loop() {
	unsigned long next = last+T;
	do {
		last = millis();
	} while (last < next);
	int v = analogRead(A0);
	tty.println(v);
	// tty.print(time);
	// tty.print('\t');
}