
#define clk 12
#define data A0
#define rst 11

void setup() {
	pinMode(clk, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(rst, OUTPUT);

	digitalWrite(clk, 0);
	digitalWrite(rst, 0);
	digitalWrite(rst, 1);
}

#define LEDBAR 8

void loop() {
	digitalWrite(10, 1);
	digitalWrite(9, 0);
	digitalWrite(8, 0);
	for(unsigned i=0; i != LEDBAR; i++) {
		digitalWrite(clk, 1);
		digitalWrite(clk, 0);
		delay(300);
	}
	digitalWrite(10, 0);
	digitalWrite(9, 1);
	digitalWrite(8, 0);
	for(unsigned i=0; i != LEDBAR; i++) {
		digitalWrite(clk, 1);
		digitalWrite(clk, 0);
		delay(300);
	}
	digitalWrite(10, 0);
	digitalWrite(9, 0);
	digitalWrite(8, 1);
	for(unsigned i=0; i != LEDBAR; i++) {
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
