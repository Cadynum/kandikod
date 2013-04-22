#include "state.h"

void Control::print(HardwareSerial *s) {
	for(unsigned int i = 0; i < FINGERS; i++) {
		s->print("Finger ");
		s->print(i);
		s->print(". Rot: ");
		s->print(this->rot[i]);
		s->print(". Bend: ");
		s->print(this->bend[i]);
		s->print("\r\n");
	}
}