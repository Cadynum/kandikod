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
	byte force[FINGERS];

	inline bool operator==(const RobotHand& rhs) const
	{
		for (unsigned i=0; i != FINGERS; i++) {
			if (force[i] != rhs.force[i])
				return false;
		}
		return true;
	}
};