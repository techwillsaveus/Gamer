/*
TO-DO
-Fix IR
-Buzzer play melody
-LDR as button event
-Scrolling text
-Gamer clear with no update
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
	_refreshRate = 50;
	ldrThreshold = 300;
	
	// Setup outputs
	pinMode(3, OUTPUT);
	for(int i=6; i<=10; i++) pinMode(i, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(13, OUTPUT);
	
	// Setup inputs
	DDRC = B00000;
	PORTC = B11111;
	
	// Change analogue read resolution to 8-bit.
	 ADCSRA &= ~(1 << ADPS2);
	
	// Timer 2 setup
	noInterrupts();
	TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(WGM22) | _BV(CS22);
	OCR2A = 51;
	OCR2B = 26;
	TCCR2B = (TCCR2B & 0b00111000) | 0x2;
	TIMSK2 = _BV(OCIE2B);
	interrupts();
}

// Inputs --------------------------------

// Returns true if a button has been pressed recently
bool Gamer::isPressed(uint8_t input) {
	if(buttonFlags[input]) {
		buttonFlags[input] = 0;
		return true;
	}
	else return false;
}

// Returns true if the button is currently held down
bool Gamer::isHeld(uint8_t input) {
	bool result = (PINC & (1<<input)) >> input;
	return !result;
}

// Returns the current value of the LDR
int Gamer::ldrValue() {
	return analogRead(LDR);
}

// Change the button threshold for the LDR.
void Gamer::setldrThreshold(uint16_t threshold) {
	ldrThreshold = threshold;
}

// Outputs -------------------------------

// Set the display's refresh rate. 1 = 1 row per timer cycle. 10 = 1 row every 10 timer cycles
void Gamer::setRefreshRate(uint16_t refreshRate) {
	_refreshRate = refreshRate;
}

// Burns the display[][] array onto the display. Only call when you're done changing pixels!
void Gamer::updateDisplay() {
	byte newImage[8];
	for(int j=0; j<8; j++) {
		newImage[j] = 0x00;
		for(int i=0; i<8; i++) {
			newImage[j] <<= 1;
			newImage[j] |= display[i][j];
		}
	}
	if(newImage != image) {
		for(int i=0; i<8; i++) image[i] = newImage[i];
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

void Gamer::enableIRTX() {
	noInterrupts();
	TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(WGM22) | _BV(CS22);
	OCR2A = 51;
	OCR2B = 26;
	TCCR2B = (TCCR2B & 0b00111000) | 0x2;
	interrupts();
}

void Gamer::disableIRTX() {
	noInterrupts();
	TCCR2A = 0;
	TCCR2B = 0;
	TCNT2 = 0;
	interrupts();
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
    	digitalWrite(DAT, (dataOut & (1<<x)) >> x);
    	digitalWrite(CLK1, HIGH);
  	}

	digitalWrite(LAT, HIGH);
	digitalWrite(LAT, LOW);
	digitalWrite(OE, LOW);
}

// Write to the MIC5891 shift register (anodes)
void Gamer::writeToRegister(byte dataOut) {
	digitalWrite(LAT, LOW);
	
	for(int y=0; y<=7; y++) {
		digitalWrite(DAT, (dataOut & (1<<y)) >> y);
		digitalWrite(CLK2, HIGH);
		digitalWrite(CLK2, LOW);
	}
	digitalWrite(LAT, HIGH);
	digitalWrite(LAT, LOW);
}

// Periodically check if inputs are pressed (+ debouncing)
void Gamer::checkInputs() {
	int currentInputState[6];
	for(int i=0; i<6; i++) {
		if(i != 5) {
			currentInputState[i] = (PINC & (1<<i)) >> i;
			if(currentInputState[i] != lastInputState[i]) {
				if(currentInputState[i] == 0) {
					buttonFlags[i] = 1;
				}
			}
			lastInputState[i] = currentInputState[i];
		}
		else {
			currentInputState[i] = analogRead(LDR);
			if(currentInputState[i] - lastInputState[i] >= ldrThreshold) buttonFlags[i] = 1;
			lastInputState[i] = currentInputState[i];
		}
	}
}

// Run Interrupt Service Routine tasks
void Gamer::isrRoutine() {
	buzzerCount++;
	pulseCount++;
	if(pulseCount >= _refreshRate) {
		updateRow();
		pulseCount = 0;
	}
	if(pulseCount == _refreshRate/2) {
		checkInputs();
	}
}