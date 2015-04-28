/*
This example shows you how to do an animation on the
Gamer's screen. Remember that you can use our awesome
animation generator to automagically convert your
animations into code that can be read by the Gamer!
*/

// Include Gamer library
#include <Gamer.h>

// Create a copy of the Gamer library.
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

// -- Animation code ends here.

void setup() {
  // Start up Gamer.
  gamer.begin();
}

void loop() {
  // Loop through all frames.
  for(int i=0; i<NUMFRAMES; i++) {
  	// Show the current frame.
    gamer.printImage(frames[i]);
    // Wait so that we can see the frame. 
    delay(200);
  }
}
