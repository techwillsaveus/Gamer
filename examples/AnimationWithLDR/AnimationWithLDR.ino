// Load in the Gamer library
#include <Gamer.h>

// Make an instance of the library
Gamer gamer;

int currentFrame;

// Animation code from our Animation generator app!
// Replace this with yours!
#define NUMFRAMES 6
byte frames[NUMFRAMES][8] = {
		{B00000000,
		B00000000,
		B00000000,
		B00011000,
		B00011000,
		B00000000,
		B00000000,
		B00000000},

		{B00000000,
		B00000000,
		B00100100,
		B00011000,
		B00011000,
		B00100100,
		B00000000,
		B00000000},

		{B00000000,
		B01000010,
		B00100100,
		B00011000,
		B00011000,
		B00100100,
		B01000010,
		B00000000},

		{B00000000,
		B01011010,
		B00100100,
		B01011010,
		B01011010,
		B00100100,
		B01011010,
		B00000000},

		{B00011000,
		B01011010,
		B00100100,
		B11011011,
		B11011011,
		B00100100,
		B01011010,
		B00011000},

		{B10011001,
		B01011010,
		B00100100,
		B11011011,
		B11011011,
		B00100100,
		B01011010,
		B10011001}};


void setup() {
  // Set up Gamer
  gamer.begin();
}

void loop() {
  // Convert LDR value to a frame.
  currentFrame = map(gamer.ldrValue(), 0, 1023, 0, NUMFRAMES);
  
  // Print current frame!
  gamer.printImage(frames[currentFrame]);
  delay(10);
}
