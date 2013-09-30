#include "Gamer.h"

// Variables
// volatile byte pulseCount;
// volatile byte nextRow;
// byte currentRow;
// byte counter;

Gamer Gamer1; // Preinstantiate
/*
// Interrupt service routine
ISR(TIMER2_COMPB_vect) {
	pulseCount++;
	if(pulseCount >= 50) {
		nextRow = 1;
		pulseCount = 0;
	}
}
*/

// Interrupt service routine
ISR(TIMER2_COMPB_vect) {
	Gamer1.isrCallback();
}

Gamer::Gamer() {
	
}

void Gamer::begin() {
	currentRow = 0x80;
	
	pinMode(3, OUTPUT);
	TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // Just enable output on Pin 3 and disable it on Pin 11
	TCCR2B = _BV(WGM22) | _BV(CS22);
	OCR2A = 52; // defines the frequency 51 = 38.4 KHz, 54 = 36.2 KHz, 58 = 34 KHz, 62 = 32 KHz
	OCR2B = 26;  // deines the duty cycle - Half the OCR2A value for 50%
	TCCR2B = TCCR2B & 0b00111000 | 0x2;
	
	TIMSK2 = _BV(OCIE2B); // Enable output compare match b
	
	//Gamer1.currentRow = 0x80;
	//isrCallback = Gamer1.refreshDisplay;
	
}

void Gamer::updateDisplay() {
	for(int j=0; j<8; j++) {
		image[j] = 0x00;
		for(int i=0; i<8; i++) {
			image[j] <<= 1;
			image[j] |= display[i][j];
		}
	}
}

void Gamer::clear() {
	for(int j=0; j<8; j++) {
		for(int i=0; i<8; i++) display[i][j] = 0;
	}
	updateDisplay();
}

// Display updating
void Gamer::update() {
	if(nextRow) {
		updateRow();
		nextRow = 0;
	}
}

void Gamer::refreshDisplay() {
	digitalWrite(13, HIGH);
	Gamer1.pulseCount++;
	if(Gamer1.pulseCount >= 50) {
		Gamer1.updateRow();
		Gamer1.pulseCount = 0;
	}
}

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
