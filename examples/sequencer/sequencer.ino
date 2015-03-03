#include <Gamer.h>


Gamer gamer;


int buttonxPos = 0;
int buttonyPos = 0;
int currNote;

long  prevDecay;
long  noteInterval = 50;

int upB;
int downB;
int leftB;
int rightB;
int startB;
int tempoB;

int noteOn;

byte counter[8];
byte noteGrid[8];
byte finalImage[8];
byte byCo[8] = {1,2,4,8,16,32,64,128};
int notes[8] = {110,120,130,140,150,160,170,180};
int tempoCounts[5]={50,100,200,300,400};
int currTemp;
int noteStep[8];
long previousMillis = 0;      
 long interval = 100;

void setup(){
 gamer.begin(); 
 Serial.begin(9600);
}

void loop(){
if(analogRead(LDR) > 350){
 if(tempoB != 1){
  tempoB = 1; 
  currTemp++;
  if(currTemp > 4){
    currTemp = 0;
  }
}
} else {
  tempoB = 0;
}
interval = tempoCounts[currTemp];
  
    unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
   if(currNote > 6){
     currNote = 0;
   } else {
   currNote++;
   }
  }


  if(gamer.isHeld(UP)){
    if(upB!= 1){
   buttonyPos--;
   upB = 1;
    }
   } else {
     upB = 0;
   }
   
    if(gamer.isHeld(DOWN)){
      if(downB!= 1){
   buttonyPos++;
   downB = 1;
      }
   } else {
     downB = 0;
   }
   
    if(gamer.isHeld(LEFT)){
      if(leftB!= 1){
   buttonxPos++;
   leftB = 1;
      }
   } else {
     leftB = 0;
   }
    if(gamer.isHeld(RIGHT)){
      if(rightB!= 1){
   buttonxPos--;
   rightB = 1;
   }
    } else {
    rightB = 0;
    }
    if(buttonyPos>7){
  buttonyPos = 0;
 }
 if(buttonyPos<0){
   buttonyPos = 7;
 }
if(buttonxPos>7){
buttonxPos = 0;
}
if(buttonxPos<0){
  buttonxPos = 7;
}

if(gamer.isHeld(START)){
if(startB!= 1){
  if(noteOn!= 1){
startB = 1;
noteGrid[buttonyPos] = byCo[buttonxPos];
noteStep[buttonyPos] = buttonxPos;
noteOn = 1;
  } else {
    startB = 1;
    noteStep[buttonyPos] = 0;
    noteGrid[buttonyPos] = 0;
    noteOn = 0;
  }
}
} else {
 startB = 0; 
}



for(int i = 0 ; i < 8; i ++){
  counter[i] = 0;
}
counter[currNote] = ~0; 
counter[buttonyPos] = byCo[buttonxPos];
for(int j = 0; j < 8; j++){
  finalImage[j] = counter[j] | noteGrid[j];
}
//Serial.println(noteGrid[currNote]);
if(noteGrid[currNote] == 0){
  gamer.stopPlay();
} else {
 gamer.play(notes[noteStep[currNote]]);

}
gamer.printImage(finalImage);

}
