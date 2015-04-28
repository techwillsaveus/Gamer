/*
A cool jumping alien. We have 3 images,
which we will display on the Gamer screen
one after another to make an animation. 
*/

// Include Gamer library
#include <Gamer.h>

// Create a copy of the Gamer library.
Gamer gamer;

// Here are three images we will animate.
byte alien1[] = {
  B00000000,
  B00000000,
  B01111110,
  B01011010,
  B01111110,
  B00100100,
  B00100100,
  B01100110
};

byte alien2[] = {
  B00000000,
  B01111110,
  B01011010,
  B01111110,
  B00100100,
  B01000010,
  B11000011,
  B00000000
};

byte alien3[] = {
  B01111110,
  B01011010,
  B01111110,
  B10100101,
  B11000011,
  B00000000,
  B00000000,
  B00000000
};

void setup() {
  // Start up Gamer.
  gamer.begin();
}

void loop() {
  // Show images, with a small delay in between.
  gamer.printImage(alien1);
  delay(500);
  gamer.printImage(alien2);
  delay(500);
  gamer.printImage(alien3);
  delay(500);
  gamer.printImage(alien3);
  delay(500);
  gamer.printImage(alien2);
  delay(500);
  gamer.printImage(alien1);
  delay(500);
}

