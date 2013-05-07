#pragma once
#include <Arduino.h>

#define SENSORS 6
#define FINGERS 3

//Always aligned because of byte
struct Control {
	byte flex[SENSORS];
	void print(HardwareSerial *s);
	void print(Serial_ *s);
};

struct RobotHand {
	byte pressure[FINGERS];
};