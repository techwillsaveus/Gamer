byte x=0;
int delayMils = 300; //larger = easier
byte framesSimon[4][8];
byte go[8];
byte right[8];
byte wrong[8];
volatile byte sequence[30];

void resetSimon() {
  gamer.clear();
  delay(100);
  for(byte b=0;b<x;b++) sequence[b]=0;
  x=0;
  delayMils = 300;
}

void simonLoop() {
  sequence[x]=random(0,4);
  if(x>0) {
    for(byte p=3;p>0;p--) {
      showScore(0,p);
      delay(delayMils);
    }
    gamer.printImage(go); //move this later...
    delay(delayMils);
    for(int i=0;i<x;i++) {
      if(gamer.isHeld(START)) return;
      gamer.printImage(framesSimon[sequence[i]]);
      delay(delayMils);
      gamer.clear();
      delay(delayMils);
    }
    gamer.clear();
    boolean success = true;
    for(byte count=0;count<x;count++) {
      if(gamer.isHeld(START)) return;
      byte key = 4;
      while(key==4) { //wait for a keypress
        if(gamer.isHeld(START)) return;
        if(gamer.isPressed(UP)) key=0;
        if(gamer.isPressed(DOWN)) key=1;
        if(gamer.isPressed(LEFT)) key=2;
        if(gamer.isPressed(RIGHT)) key=3;
      }
      gamer.printImage(framesSimon[key]);
      //is it riiggghhhttt???
      if(key!=sequence[count]) {
        success = false; // game over...
        break;
      }
    }
    delayMils-=(delayMils/40);
    delay(delayMils);
    if(success) {
      x++; //they got it right, MAKE IT HARDER!
      gamer.printImage(right);
    } 
    else {
      gamer.printImage(wrong);
      delay(500);
      showScore((x-1)/10,(x-1)%10); //showScore wants digits, not numbers! (as in 1,5 rather than 15)
      delay(500);
      resetSimon();
    }
  } else {
    x++; //rack up the difficulty anyway!
  }
  delay(500);
}

void setupSimonImages() {
  framesSimon[0][0] = B00000000; //up
  framesSimon[0][1] = B00011000;
  framesSimon[0][2] = B00111100;
  framesSimon[0][3] = B01111110;
  framesSimon[0][4] = B00011000;
  framesSimon[0][5] = B00011000;
  framesSimon[0][6] = B00011000;
  framesSimon[0][7] = B00000000;
  framesSimon[1][7] = B00000000; //down (aka up, but flipped)
  framesSimon[1][6] = B00011000;
  framesSimon[1][5] = B00111100;
  framesSimon[1][4] = B01111110;
  framesSimon[1][3] = B00011000;
  framesSimon[1][2] = B00011000;
  framesSimon[1][1] = B00011000;
  framesSimon[1][0] = B00000000;
  framesSimon[2][0] = B00000000; //left
  framesSimon[2][1] = B00010000;
  framesSimon[2][2] = B00110000;
  framesSimon[2][3] = B01111110;
  framesSimon[2][4] = B01111110;
  framesSimon[2][5] = B00110000;
  framesSimon[2][6] = B00010000;
  framesSimon[2][7] = B00000000;
  framesSimon[3][0] = B00000000; //right (left but flipped)
  framesSimon[3][1] = B00001000;
  framesSimon[3][2] = B00001100;
  framesSimon[3][3] = B01111110;
  framesSimon[3][4] = B01111110;
  framesSimon[3][5] = B00001100;
  framesSimon[3][6] = B00001000;
  framesSimon[3][7] = B00000000;
  go[0] = B00000000;
  go[1] = B01101110;
  go[2] = B10001010;
  go[3] = B10001010;
  go[4] = B10001010;
  go[5] = B10101010;
  go[6] = B01101110;
  go[7] = B00100000;
  wrong[0] = B11000011;
  wrong[1] = B01100110;
  wrong[2] = B00111100;
  wrong[3] = B00011000;
  wrong[4] = B00011000;
  wrong[5] = B00111100;
  wrong[6] = B01100110;
  wrong[7] = B11000011;
  right[0] = B00000001;
  right[1] = B00000011;
  right[2] = B00000111;
  right[3] = B00001110;
  right[4] = B11011100;
  right[5] = B11111000;
  right[6] = B01110000;
  right[7] = B00100000;
}



