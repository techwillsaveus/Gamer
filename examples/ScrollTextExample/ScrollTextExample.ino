/*
This example shows you how to scroll text
across the Gamer's screen. 
*/

// Include Gamer library
#include <Gamer.h>

// Create a copy of the Gamer library
Gamer gamer;

void setup() {
  // Start up Gamer.
  gamer.begin();
}

void loop() {
  // Print "Hello world"
  gamer.printString("Hello world! :D");
}
