#pragma once
#include <Arduino.h>

#define FINGERS 3

//Always aligned because of byte
struct Control {
	byte rot[FINGERS];
	byte bend[FINGERS];
	void print(HardwareSerial *s);
};