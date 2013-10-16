
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
	#define START 4
	#define LDR 5
	
	// Setup
	void begin();
	void update();
	
	// Inputs
	bool isPressed(uint8_t input);
	bool isHeld(uint8_t input);
	
	// Outputs
	void updateDisplay();
	void allOn();
	void clear();
	void printImage(byte* img);
	void setLED(bool value);
	void toggleLED();
	
	// Variables
	byte display[8][8];
	byte pulseCount;
	byte buzzerCount;
	byte nextRow;
	byte currentRow;
	byte counter;
	byte image[8];
	
	void isrRoutine();
	
private:
	
	// Keywords
	#define CLK1 6
	#define DAT1 8
	#define LAT1 9
	#define CLK2 7
	#define DAT2 8
	#define LAT2 9
	#define OE 10
	#define LED 13
	#define BUZZER 2
	#define RX 5
	#define TX 4
	
	// Variables
	
	// Functions
	void writeToDriver(byte dataOut);
	void writeToRegister(byte dataOut);
	void checkSerial();
	void updateRow();
	
};

#endif