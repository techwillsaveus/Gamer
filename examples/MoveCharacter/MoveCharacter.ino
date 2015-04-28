/*
This example shows you how to move a character around the 
screen by pressing the buttons. 

We are mainly using the printImage function, but we're
telling it to print the image in a specific position!
*/

// Include Gamer library.
#include <Gamer.h>

// Create a copy of the Gamer library.
Gamer gamer;

// This is where we store the position of our character!
int xPos, yPos;

/* 
Replace this with your own character! We drew this with our
Image Painter tool, clicked on "copy code" and pasted it here.
*/
byte character[8] = {B10010000,
                     B01100000,
                     B01100000,
                     B10010000,
                     B00000000,
                     B00000000,
                     B00000000,
                     B00000000};

void setup() {
  // Start up Gamer.
  gamer.begin();
}

void loop() {
  // Print the character in the right position.
  gamer.printImage(character, xPos, yPos);
  
  // Change the position of the character depending on the button presses.
  if(gamer.isPressed(UP)) {
    yPos--;
    gamer.clear();
  }
  else if(gamer.isPressed(DOWN)) {
    yPos++;
    gamer.clear();
  }
  if(gamer.isPressed(LEFT)) {
    xPos--;
    gamer.clear();
  }
  else if(gamer.isPressed(RIGHT)) {
    xPos++;
    gamer.clear();
  }
}