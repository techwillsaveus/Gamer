#ifndef GamerIR_h
#define GamerIR_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class GamerIR {
public:
	GamerIR();

	SoftwareSerial _serial;

	void irSend(String message);
	String irReceive();

private:
	char prevChar;
};

#endif
