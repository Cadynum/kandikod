#include "state.h"

void Control::print(HardwareSerial *s) {
	for(size_t i = 0; i < SENSORS; i+=2) {
		s->print("Finger ");
		s->print(i);
		s->print(". Rot: ");
		s->print(this->flex[i]);
		s->print(". Bend: ");
		s->print(this->flex[i+1]);
		s->print("\r\n");
	}
}

void Control::print(Serial_ *s) {
	for(size_t i = 0; i < SENSORS; i+=2) {
		s->print("Finger ");
		s->print(i);
		s->print(". Rot: ");
		s->print(this->flex[i]);
		s->print(". Bend: ");
		s->print(this->flex[i+1]);
		s->print("\r\n");
	}
}

// size_t Print::print(const Control &ctl) {
// 	for(size_t i = 0; i < FINGERS; i++) {
// 		print("Finger ");
// 		print(i);
// 		print(". Rot: ");
// 		print(ctl.rot[i]);
// 		print(". Bend: ");
// 		print(ctl.bend[i]);
// 		print("\r\n");
// 	}
// }