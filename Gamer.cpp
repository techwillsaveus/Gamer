/*
TO-DO
-Fix IR
-Button events
-Buzzer play melody
-LDR as button event
-Scrolling text?
*/


#include "Gamer.h"

Gamer *thisGamer = NULL;

// Interrupt service routine
ISR(TIMER2_COMPB_vect) {
	thisGamer->isrRoutine();
}

Gamer::Gamer() {
}

// Setup inputs, outputs, timers, etc. Call this from setup()!!
void Gamer::begin() {
	::thisGamer = this;
	pinMode(3, OUTPUT);
	pinMode(2, OUTPUT);
	for(int i=6; i<=10; i++) pinMode(i, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(13, OUTPUT);
	TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(WGM22) | _BV(CS22);
	OCR2A = 51; // defines the frequency 51 = 38.4 KHz, 54 = 36.2 KHz, 58 = 34 KHz, 62 = 32 KHz
	OCR2B = 26;
	TCCR2B = (TCCR2B & 0b00111000) | 0x2;
	TIMSK2 = _BV(OCIE2B); // Enable output compare match b
}

// Burns the display[][] array onto the display. Only call when you're done changing pixels!
void Gamer::updateDisplay() {
	for(int j=0; j<8; j++) {
		image[j] = 0x00;
		for(int i=0; i<8; i++) {
			image[j] <<= 1;
			image[j] |= display[i][j];
		}
	}
}

// Turn on all pixels on display
void Gamer::allOn() {
	for(int j=0; j<8; j++) {
		for(int i=0; i<8; i++) display[i][j] = 1;
	}
	updateDisplay();
}

void Gamer::clear() {
	for(int j=0; j<8; j++) {
		for(int i=0; i<8; i++) display[i][j] = 0;
	}
	updateDisplay();
}

// Print an 8 byte array onto the display
void Gamer::printImage(byte* img) {
	for(int j=0; j<8; j++) {
		for(int i=0; i<8; i++) {
			display[i][j] = (img[j] & (1 << (7-i))) != 0;
		}
	}
	updateDisplay();
}

// Set the value of the Gamer LED
void Gamer::setLED(bool value) {
	digitalWrite(LED, value);
}

// Toggle the Gamer LED
void Gamer::toggleLED() {
	digitalWrite(LED, !digitalRead(LED));
}

// Internal display refreshing and writing to ICs ----------------------

// Load the next row in the display.
void Gamer::updateRow() {
	if(counter==8) {
		counter = 0;
		currentRow = 0x80;
	}
	writeToRegister(0);
	writeToDriver(image[counter]);
	writeToRegister(currentRow);
	currentRow >>= 1;
	counter++;
}

// Writes to the TLC5916 LED driver (cathodes)
void Gamer::writeToDriver(byte dataOut) {
	digitalWrite(OE, HIGH);
	
	for(int x=0; x<=7; x++) {
    	digitalWrite(CLK1, LOW);
    	digitalWrite(DAT1, (dataOut & (1<<x)) >> x);
    	digitalWrite(CLK1, HIGH);
  	}

	digitalWrite(LAT1, HIGH);
	digitalWrite(LAT1, LOW);
	digitalWrite(OE, LOW);
}

// Write to the MIC5891 shift register (anodes)
void Gamer::writeToRegister(byte dataOut) {
	digitalWrite(LAT2, LOW);
	
	for(int y=0; y<=7; y++) {
		digitalWrite(DAT2, (dataOut & (1<<y)) >> y);
		digitalWrite(CLK2, HIGH);
		digitalWrite(CLK2, LOW);
	}
	digitalWrite(LAT2, HIGH);
	digitalWrite(LAT2, LOW);
}

// Run Interrupt Service Routine tasks
void Gamer::isrRoutine() {
	buzzerCount++;
	pulseCount++;
	if(pulseCount >= 50) {
		updateRow();
		pulseCount = 0;
	}
}