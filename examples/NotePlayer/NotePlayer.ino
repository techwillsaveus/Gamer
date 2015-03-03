#include <Gamer.h>

byte up[8] = {B00011000,
              B00111100,
              B01111110,
              B11111111,
              B00011000,
              B00011000,
              B00011000,
              B00011000};

byte right[8] = {B00001000,
                 B00001100,
                 B00001110,
                 B11111111,
                 B11111111,
                 B00001110,
                 B00001100,
                 B00001000};
                 
                 byte down[8] = {B00011000,
                B00011000,
                B00011000,
                B00011000,
                B11111111,
                B01111110,
                B00111100,
                B00011000};
                
 byte left[8] = {B00010000,
                B00110000,
                B01110000,
                B11111111,
                B11111111,
                B01110000,
                B00110000,
                B00010000};



Gamer gamer;


void setup() {
  gamer.begin();
}

void loop() {
  if(gamer.isPressed(UP)){
      gamer.printImage(up);
      gamer.play(200);
  }
   if(gamer.isPressed(RIGHT)){
      gamer.printImage(right);
      gamer.play(220);
  }
   if(gamer.isPressed(DOWN)){
      gamer.printImage(down);
      gamer.play(240);
  }
   if(gamer.isPressed(LEFT)){
      gamer.printImage(left);
      gamer.play(180);
  }
  if(gamer.isHeld(UP) == false && gamer.isHeld(DOWN) == false && gamer.isHeld(LEFT) == false && gamer.isHeld(RIGHT) == false){
 
  gamer.stopPlay();
  }
}



