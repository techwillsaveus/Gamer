#include <Gamer.h>

Gamer gamer;

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
  gamer.begin();
  gamer.setLED(HIGH);
}

void loop() {
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

