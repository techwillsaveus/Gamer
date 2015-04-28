/*
This example shows you how to play tones on the
Gamer's buzzer. Press one of the buttons, and you'll
hear a sound. 
*/

// Include Gamer library.
#include <Gamer.h>

// Images displayed when the buttons are pressed.
byte up[8] = {
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B00011000,
  B00011000,
  B00011000,
  B00011000};

byte right[8] = {
  B00001000,
  B00001100,
  B00001110,
  B11111111,
  B11111111,
  B00001110,
  B00001100,
  B00001000};

byte down[8] = {
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B11111111,
  B01111110,
  B00111100,
  B00011000};

byte left[8] = {
  B00010000,
  B00110000,
  B01110000,
  B11111111,
  B11111111,
  B01110000,
  B00110000,
  B00010000};

// Create a copy of the Gamer library.
Gamer gamer;

void setup() {
  // Start up Gamer.
  gamer.begin();
}

void loop() {
  /* 
  Depending on the button that's held down,
  play a note!
  */
  if(gamer.isHeld(UP)) {
    gamer.printImage(up);
    gamer.playTone(200);
  }
  else if(gamer.isHeld(RIGHT)) {
    gamer.printImage(right);
    gamer.playTone(220);
  }
  else if(gamer.isHeld(DOWN)) {
    gamer.printImage(down);
    gamer.playTone(240);
  }
  else if(gamer.isHeld(LEFT)) {
    gamer.printImage(left);
    gamer.playTone(180);
  }
  // Otherwise, silence!
  else gamer.stopTone();
}


