// Include the DIY Gamer library
#include <Gamer.h>

// Make a copy of the library
Gamer gamer;

// Animation code copied from our Animation Generator app.
#define NUMFRAMESIMAGES 4
byte images[NUMFRAMESIMAGES][8] = {
  {
    B00011000,
    B00111100,
    B01111110,
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000  }
  ,

  {
    B00010000,
    B00110000,
    B01110000,
    B11111111,
    B11111111,
    B01110000,
    B00110000,
    B00010000  }
  ,

  {
    B00001000,
    B00001100,
    B00001110,
    B11111111,
    B11111111,
    B00001110,
    B00001100,
    B00001000  }
  ,

  {
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11111111,
    B01111110,
    B00111100,
    B00011000  }
};

void setup() {
  // Start Gamer!
  gamer.begin();
}

void loop() {
  if(gamer.isPressed(UP)) {
    gamer.printImage(images[0]);
    delay(200);
  }
  else if(gamer.isPressed(LEFT)) {
    gamer.printImage(images[1]);
    delay(200);
  } 
  else if(gamer.isPressed(RIGHT)) {
    gamer.printImage(images[2]);
    delay(200);
  } 
  else if(gamer.isPressed(DOWN)) {
    gamer.printImage(images[3]);
    delay(200);
  }
  
  gamer.clear();
}
