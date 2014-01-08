// Load in the Gamer library
#include <Gamer.h>

// Make an instance of the library
Gamer gamer;

// Animation code from our Animation generator app!
// Replace this with yours!
#define NUMFRAMES 5
byte frames[NUMFRAMES][8] = {
		{B00000000,
		B00000000,
		B00100100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000000},

		{B00000000,
		B00000000,
		B00100100,
		B00000000,
		B00011000,
		B00111100,
		B00011000,
		B00000000},

		{B00000000,
		B00000000,
		B00100100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000000},

		{B00000000,
		B00000000,
		B00100100,
		B00000000,
		B00000000,
		B00111100,
		B00011000,
		B00000000},

		{B00000000,
		B00000000,
		B00100100,
		B00000000,
		B00000000,
		B00111100,
		B00011000,
		B00011000}};


void setup() {
  // Set up Gamer
  gamer.begin();
}

void loop() {
  // Loop through all frames
  for(int i=0; i<NUMFRAMES; i++) {
    gamer.printImage(frames[i]);
    delay(200);
  }
}
