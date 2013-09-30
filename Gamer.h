
#ifndef Gamer_h
#define Gamer_h

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>

class Gamer {
public:
	Gamer();
	// Keywords
	#define UP 0
	#define LEFT 1
	#define RIGHT 2
	#define DOWN 3
	
	// Setup
	void begin();
	void update();
	
	// Inputs
	bool leftPressed();
	bool rightPressed();
	bool upPressed();
	bool downPressed();
	bool ldrPressed();	
	bool startPressed();
	
	// Outputs
	void updateDisplay();
	static void refreshDisplay();
	void clear();
	void setLED(bool value);
	void playNote(int note);
	void playNote(int note, int duration);
	void playFrequency(int freq);
	byte display[8][8];
	
	// Variables
	byte image[8];
	static byte pulseCount;
	byte nextRow;
	byte currentRow;
	static byte counter;
	
	void (*isrCallback)();
	
	// Functions
	void writeToDriver(byte dataOut);
	void writeToRegister(byte dataOut);
	void updateRow();
	
private:
	
	// Keywords
	#define CLK1 6
	#define DAT1 8
	#define LAT1 9
	#define CLK2 7
	#define DAT2 8
	#define LAT2 9
	#define OE 10
	
	
};

extern Gamer Gamer1;
#endif