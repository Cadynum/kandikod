#pragma once
#include <Arduino.h>

#define SENSORS 6

//Always aligned because of byte
struct Control {
	byte flex[SENSORS];
	void print(HardwareSerial *s);
	void print(Serial_ *s);
};