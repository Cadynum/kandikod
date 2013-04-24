#pragma once
#include <Arduino.h>

void send_bytes(HardwareSerial *s, const byte *buf, const unsigned int len);
boolean recv_bytes(HardwareSerial *s, byte *buf, const unsigned int len);