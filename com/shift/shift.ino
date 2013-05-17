
#define clk A5
#define data A0
#define rst A1

void setup() {
	pinMode(clk, OUTPUT);
	pinMode(data, OUTPUT);
	pinMode(rst, OUTPUT);

	digitalWrite(clk, 0);
	digitalWrite(rst, 0);
	digitalWrite(rst, 1);
}

#define LEDBAR 8

void loop() {
	for(unsigned i=0; i != LEDBAR; i++) {
		digitalWrite(data, 1);
		digitalWrite(clk, 1);
		digitalWrite(clk, 0);
		delay(300);
	}
	delay(200);
	digitalWrite(rst, 0);
	digitalWrite(rst, 1);
	// delay(1000);
	// for(unsigned i=0; i != LEDBAR; i++) {
	// 	digitalWrite(data, 0);
	// 	digitalWrite(clk, 1);
	// 	digitalWrite(clk, 0);
	// 	delay(300);
	// }
	delay(200);
}
