#include <SoftwareSerial.h>

#include <Gamer.h>

Gamer gamer;

int currentX = 0;
int currentY = 0;
int dir = 1;
int goalX = random(0,7);
int goalY = random(0,7);
int snakeMap[8][8];
int snakeLength = 2;
byte frames[11][8];
int score = 0;
byte letters[53][8];
byte numbers[10][2][8];
byte n1[8],n1b[8],n2[8],n2b[8],n3[8],n3b[8],n4[8],n4b[8],n5[8],n5b[8],n6[8],n6b[8],n7[8],n7b[8],n8[8],n8b[8],n9[8],n9b[8],n0[8],n0b[8];

void setup() {
  Serial.begin(9600);
  gamer.begin();
  //setupScore();
}

void setupStuff() {
  snakeLength = 2;
  score = 0;
  goalX = random(0,7);
  goalY = random(0,7);
  currentX = 0;
  currentY = 0;
  for(int x=0;x<8;x++) {
    for(int y=0;y<8;y++) {
      snakeMap[x][y] = 0;
    }
  }
  gamer.updateDisplay();
}

void loop() {
  //gamer.clear, but DON'T UPDATE YET!!!!
  for(int x=0;x<8;x++) {
    for(int y=0;y<8;y++) {
      gamer.display[x][y] = LOW;
    }
  }
  //buttons should be here!
  //when upPressed etc. has been added, uncomment this next section and then comment out the random directions section:
  
  if(gamer.isPressed(UP)) dir=1;
  if(gamer.isPressed(RIGHT)) dir=2;
  if(gamer.isPressed(DOWN)) dir=3;
  if(gamer.isPressed(LEFT)) dir=4;
  
  //this is a random directions function. comment it out when button support has been added
  //if(random(0,10)>7) dir++;
  //if(dir>4) dir=1;
  //this is the end of a random directions function.
  if(dir==1) {
    currentY--;
    if(currentY<0) currentY=7;
  } else if(dir==2) {
    currentX++;
    if(currentX>7) currentX=0;
  } else if(dir==3) {
    currentY++;
    if(currentY>7) currentY=0;
  } else if(dir==4) {
    currentX--;
    if(currentX<0) currentX=7;
  }
  gamer.display[currentX][currentY] = HIGH;
  snakeRec();
  isCollected();
  delay(150);
  gamer.updateDisplay();
}

void isCollected() {
  if(currentX==goalX && currentY==goalY) {
    goalX = random(0,7);
    goalY = random(0,7);
    snakeLength++;
    score++;
    for(int x=0;x<8;x++) {
      for(int y=0;y<8;y++) {
        snakeMap[x][y]++;
      }
    }
  } else {
    gamer.display[goalX][goalY] = HIGH;
  }
}

void snakeRec() {
  for(int x=0;x<8;x++) {
    for(int y=0;y<8;y++) {
      if(snakeMap[x][y] > 0) {
        snakeMap[x][y]--;
      }
    }
  }
  collided();
  snakeMap[currentX][currentY] = snakeLength;
  for(int x=0;x<8;x++) {
    for(int y=0;y<8;y++) {
      if(snakeMap[x][y] > 0) {
        gamer.display[x][y] = HIGH;
      }
    }
  }
}

void collided() {
  for(int x=0;x<8;x++) { //it seems to work if I add this :p
    for(int y=0;y<8;y++) {
      if(snakeMap[x][y] > 0) {
        if(currentX == x && currentY == y) {
          gamer.clear();
          delay(20);
          printString("GAME OVER  your score is");
          int dig2 = score % 10;  //split score into two digits (eg 10 -> 1 and 0)
          int dig1 = (score-(score%10))/10;
          showScore(score);
          delay(500);
          setupStuff();
        }
      }
    }
  }
}

//everything below here is for showScore() and printString()
#define LETEND B10101010

byte allLetters[53][9] = {
   {B00000000,B00000000,B00000000,LETEND},   // space
   {B01111110,B10010000,B10010000,B10010000,B01111110,B00000000,LETEND}, // A
   {B11111110,B10010010,B10010010,B10010010,B01101100,B00000000,LETEND}, // B
   {B01111100,B10000010,B10000010,B10000010,B01000100,B00000000,LETEND}, // C
   {B11111110,B10000010,B10000010,B01000100,B00111000,B00000000,LETEND}, // D
   {B11111110,B10010010,B10010010,B10010010,B10000010,B00000000,LETEND}, // E
   {B11111110,B10010000,B10010000,B10010000,B10000000,B00000000,LETEND}, // F
   {B01111100,B10000010,B10001010,B10001100,B01001110,B00000000,LETEND}, // G
   {B11111110,B00010000,B00010000,B00010000,B11111110,B00000000,LETEND}, // H
   {B10000010,B11111110,B10000010,B00000000,LETEND}, // I
   {B00000100,B00000010,B10000010,B11111100,B10000000,B00000000,LETEND}, // J
   {B11111110,B00010000,B00101000,B01000100,B10000010,B00000000,LETEND}, // K
   {B11111110,B00000010,B00000010,B00000010,B00000010,B00000000,LETEND}, // L
   {B11111110,B01000000,B00100000,B01000000,B11111110,B00000000,LETEND}, // M
   {B11111110,B01100000,B00010000,B00001100,B11111110,B00000000,LETEND}, // N
   {B01111100,B10000010,B10000010,B10000010,B01111100,B00000000,LETEND}, // O
   {B11111110,B10010000,B10010000,B10010000,B01100000,B00000000,LETEND}, // P
   {B01111100,B10000010,B10000010,B10000100,B01111010,B00000000,LETEND}, // Q
   {B11111110,B10010000,B10011000,B10010100,B01100010,B00000000,LETEND}, // R
   {B01100100,B10010010,B10010010,B10010010,B01001100,B00000000,LETEND}, // S
   {B10000000,B10000000,B11111110,B10000000,B10000000,B00000000,LETEND}, // T
   {B11111100,B00000010,B00000010,B00000010,B11111100,B00000000,LETEND}, // U
   {B11100000,B00011000,B00000110,B00011000,B11100000,B00000000,LETEND}, // V
   {B11111100,B00000010,B00011100,B00000010,B11111100,B00000000,LETEND}, // W
   {B10000010,B01101100,B00010000,B01101100,B10000010,B00000000,LETEND}, // X
   {B11000000,B00100000,B00011110,B00100000,B11000000,B00000000,LETEND}, // Y
   {B10000110,B10001010,B10010010,B10100010,B11000010,B00000000,LETEND}, // Z

   {B00011100,B00100010,B00100010,B00011110,B00000000,LETEND}, // a
   {B01111110,B00010010,B00010010,B00001100,B00000000,LETEND}, // b
   {B00011100,B00100010,B00100010,B00010010,B00000000,LETEND}, // c
   {B00001100,B00010010,B00010010,B11111110,B00000000,LETEND}, // d
   {B00011100,B00101010,B00101010,B00011010,B00000000,LETEND}, // e
   {B00111110,B01001000,B01000000,B00000000,LETEND}, // f
   {B00001101,B00010101,B00011110,B00000000,LETEND}, // g
   {B01111110,B00010000,B00001110,B00000000,LETEND}, // h
   {B01011110,B00000000,LETEND}, // i
   {B00000010,B00000010,B01011100,B00000000,LETEND}, // j
   {B11111110,B00011000,B00100110,B00000000,LETEND}, // k
   {B01111100,B00000010,B00000010,B00000000,LETEND}, // l
   {B00011110,B00100000,B00011000,B00100000,B00011110,B00000000,LETEND}, // m
   {B00111110,B00010000,B00100000,B00011110,B00000000,LETEND}, // n
   {B00011100,B00100010,B00100010,B00011100,B00000000,LETEND}, // o
   {B00111111,B00100100,B00100100,B00011000,B00000000,LETEND}, // p
   {B00011000,B00100100,B00100100,B00111111,B00000000,LETEND}, // q
   {B00111110,B00010000,B00100000,B00100000,B00000000,LETEND}, // r
   {B00010010,B00101010,B00101010,B00100100,B00000000,LETEND}, // s
   {B01111100,B00100010,B00000010,B00000000,LETEND}, // t
   {B00111100,B00000010,B00111110,B00000000,LETEND}, // u
   {B00111000,B00000110,B00111000,B00000000,LETEND}, // v
   {B00111100,B00000010,B00001100,B00000010,B00111100,B00000000,LETEND}, // w
   {B00110110,B00001000,B00110110,B00000000,LETEND}, // x
   {B00111001,B00000101,B00111110,B00000000,LETEND}, // y
   {B00100110,B00101010,B00110010,B00000000,LETEND} // z
};


void printString(String string) {
  byte screen[8]={0};
  gamer.clear();
  for( int index = 0; index<string.length(); index++ ){
    char c = string[index];
    int letIx = 0;
    if( c>='A' && c<='Z' ) letIx = c-'A'+1;
    else if( c>='a' && c<='z' ) letIx = c-'a'+1+26;
    int colIx = 0;
    byte col;
    while( (col = allLetters[letIx][colIx]) != LETEND ){
      appendColumn(screen, col);
      colIx++;
    }
  }
  for( int i=0; i<8; i++)
    appendColumn(screen, 0);
}

void appendColumn(byte* screen, byte col){
  for( int i=0; i<8; i++){
    screen[i]<<=1;
    if( (col&(1<<(7-i)))!=0 ) screen[i]++;
  }
  gamer.printImage(screen);
  delay(70);
}

byte allNumbers[10][8] = {
   { B00000010,B00000101,B00000101,B00000101,B00000101,B00000101,B00000101,B00000010 },
   { B00000010,B00000110,B00000010,B00000010,B00000010,B00000010,B00000010,B00000111 },
   { B00000010,B00000101,B00000001,B00000010,B00000010,B00000100,B00000100,B00000111 },
   { B00000111,B00000001,B00000001,B00000110,B00000001,B00000001,B00000101,B00000010 },
   { B00000100,B00000101,B00000101,B00000111,B00000001,B00000001,B00000001,B00000001 },
   { B00000111,B00000100,B00000100,B00000110,B00000001,B00000001,B00000101,B00000010 },
   { B00000011,B00000100,B00000100,B00000110,B00000101,B00000101,B00000101,B00000010 },
   { B00000111,B00000001,B00000001,B00000010,B00000010,B00000100,B00000100,B00000100 },
   { B00000010,B00000101,B00000101,B00000010,B00000101,B00000101,B00000101,B00000010 },
   { B00000010,B00000101,B00000101,B00000011,B00000001,B00000001,B00000001,B00000110 }
};

void showScore(int n) {
  byte result[8];
  int dig1=n/10;
  int dig2=n%10;
  for(int p=0;p<8;p++) {
    result[p]=allNumbers[dig2][p];
    if( dig1>0 ) 
      result[p]|=(allNumbers[dig1][p]<<4);
  }
  gamer.printImage(result);
}