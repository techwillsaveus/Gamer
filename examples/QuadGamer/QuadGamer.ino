/*
This example demonstrates how to load multiple games into the Gamer.
It's not a super straightforward process, so we thought we'd show
you an example of running four games at the same time. 

In order to have more than one game, we need to separate out all the
game logic, variables, and functions of each game into separate tabs
in the Arduino environment. 

After we do that, we can select a game from a menu screen.

This example was written by the wonderful Finnbar Keating (github: finnbar).
If you have more specific questions, give him a ping on Twitter (@_finnbar)!
*/

// Include Gamer library.
#include <Gamer.h>

// Create a copy of the Gamer library.
Gamer gamer;

byte startup[16][8]; //declare at top of code
byte snake[16][8];  //snake animation
byte breakout[13][8]; //breakout anim
byte simon[20][8]; //simon anim
byte flappy[8][8]; //flappy anim
volatile byte animationLength[] = { //how long is each animation???
  16,13,20,8};
volatile byte animationFrame = 0; //what frame is it???
volatile byte gameNumber = 0; //what game is it???
volatile byte gameMax = 4; //how many games are there???

void setup() {
  gamer.begin();
  setupLogo(); //starting anim
  setupSnake(); //snake anim
  setupBreakout(); //breakout anim
  setupSimon(); //simon says anim
  setupFlappy(); //flappy anim
  setupScore(); //printString / showScore

    setupImages(); //breakout win/lose images
  setupSimonImages(); //simon arrow and result images
  for(int i=0;i<16;i++) { //the animation
    gamer.printImage(startup[i]);
    delay(100);
  }
}

void loop() { //selector
  if(gamer.isPressed(START)) {
    //start game!
    switch(gameNumber) {
    case 0:
      //snake!
      //wait for start to be released
      setupSnakeGame(); //setup, well, snake
      while(!gamer.isPressed(START)) {
        //run the main game loop!
        snakeLoop();
      }
      break;
    case 1:
      startBreakout(true);
      //breakout
      while(!gamer.isPressed(START)) {
        breakoutLoop();
      }
      break;
    case 2:
      resetSimon();
      while(!gamer.isPressed(START)) {
        simonLoop();
      }
      break;
    case 3:
      resetFlappy();
      while(!gamer.isPressed(START)) {
        flappyLoop();
      }
      break;
    }
  } 
  else {
    //play animations!
    switch(gameNumber) {
    case 0:
      gamer.printImage(snake[animationFrame]);
      break;
    case 1:
      //breakout
      gamer.printImage(breakout[animationFrame]);
      break;//out
    case 2:
      //simon
      gamer.printImage(simon[animationFrame]);
      break;
    case 3:
      //flappy
      gamer.printImage(flappy[animationFrame]);
      break;
    }
    animationFrame++;
    if(animationFrame>animationLength[gameNumber]-1) animationFrame=0;
    //now check buttons!
    if(gamer.isPressed(LEFT)) {
      gameNumber--;
      animationFrame=0;
    }
    if(gamer.isPressed(RIGHT)) {
      gameNumber++;
      animationFrame=0;
    }
    if(gameNumber==255) gameNumber=gameMax-1;
    if(gameNumber>=gameMax) gameNumber=0;
    delay(100);
  }
}

void setupLogo() { //run this at the start
  startup[0][0] = B00000000;
  startup[0][1] = B00000000;
  startup[0][2] = B00000000;
  startup[0][3] = B00010000;
  startup[0][4] = B00001000;
  startup[0][5] = B00000000;
  startup[0][6] = B00000000;
  startup[0][7] = B00000000;
  startup[1][0] = B00000000;
  startup[1][1] = B00000000;
  startup[1][2] = B00000000;
  startup[1][3] = B00011000;
  startup[1][4] = B00011000;
  startup[1][5] = B00000000;
  startup[1][6] = B00000000;
  startup[1][7] = B00000000;
  startup[2][0] = B00000000;
  startup[2][1] = B00000000;
  startup[2][2] = B00110000;
  startup[2][3] = B00111000;
  startup[2][4] = B00011100;
  startup[2][5] = B00001100;
  startup[2][6] = B00000000;
  startup[2][7] = B00000000;
  startup[3][0] = B00000000;
  startup[3][1] = B00000000;
  startup[3][2] = B00111100;
  startup[3][3] = B00111100;
  startup[3][4] = B00111100;
  startup[3][5] = B00111100;
  startup[3][6] = B00000000;
  startup[3][7] = B00000000;
  startup[4][0] = B00000000;
  startup[4][1] = B01110000;
  startup[4][2] = B01111100;
  startup[4][3] = B01111100;
  startup[4][4] = B00111110;
  startup[4][5] = B00111110;
  startup[4][6] = B00001110;
  startup[4][7] = B00000000;
  startup[5][0] = B00000000;
  startup[5][1] = B01111110;
  startup[5][2] = B01111110;
  startup[5][3] = B01111110;
  startup[5][4] = B01111110;
  startup[5][5] = B01111110;
  startup[5][6] = B01111110;
  startup[5][7] = B00000000;
  startup[6][0] = B11110000;
  startup[6][1] = B11111110;
  startup[6][2] = B11111110;
  startup[6][3] = B11111110;
  startup[6][4] = B01111111;
  startup[6][5] = B01111111;
  startup[6][6] = B01111111;
  startup[6][7] = B00001111;
  startup[7][0] = B11111111;
  startup[7][1] = B11111111;
  startup[7][2] = B11111111;
  startup[7][3] = B11111111;
  startup[7][4] = B11111111;
  startup[7][5] = B11111111;
  startup[7][6] = B11111111;
  startup[7][7] = B11111111;
  startup[8][0] = B11111111;
  startup[8][1] = B11111111;
  startup[8][2] = B11111111;
  startup[8][3] = B11101111;
  startup[8][4] = B11110111;
  startup[8][5] = B11111111;
  startup[8][6] = B11111111;
  startup[8][7] = B11111111;
  startup[9][0] = B11111111;
  startup[9][1] = B11111111;
  startup[9][2] = B11111111;
  startup[9][3] = B11100111;
  startup[9][4] = B11100111;
  startup[9][5] = B11111111;
  startup[9][6] = B11111111;
  startup[9][7] = B11111111;
  startup[10][0] = B11111111;
  startup[10][1] = B11111111;
  startup[10][2] = B11001111;
  startup[10][3] = B11000111;
  startup[10][4] = B11100011;
  startup[10][5] = B11110011;
  startup[10][6] = B11111111;
  startup[10][7] = B11111111;
  startup[11][0] = B11111111;
  startup[11][1] = B11111111;
  startup[11][2] = B11000011;
  startup[11][3] = B11000011;
  startup[11][4] = B11000011;
  startup[11][5] = B11000011;
  startup[11][6] = B11111111;
  startup[11][7] = B11111111;
  startup[12][0] = B11111111;
  startup[12][1] = B10001111;
  startup[12][2] = B10000011;
  startup[12][3] = B10000011;
  startup[12][4] = B11000001;
  startup[12][5] = B11000001;
  startup[12][6] = B11110001;
  startup[12][7] = B11111111;
  startup[13][0] = B11111111;
  startup[13][1] = B10000001;
  startup[13][2] = B10000001;
  startup[13][3] = B10000001;
  startup[13][4] = B10000001;
  startup[13][5] = B10000001;
  startup[13][6] = B10000001;
  startup[13][7] = B11111111;
  startup[14][0] = B00000111;
  startup[14][1] = B00000001;
  startup[14][2] = B00000001;
  startup[14][3] = B00000000;
  startup[14][4] = B00000000;
  startup[14][5] = B10000000;
  startup[14][6] = B10000000;
  startup[14][7] = B11100000;
  startup[15][0] = B00000000;
  startup[15][1] = B00000000;
  startup[15][2] = B00000000;
  startup[15][3] = B00000000;
  startup[15][4] = B00000000;
  startup[15][5] = B00000000;
  startup[15][6] = B00000000;
  startup[15][7] = B00000000;
}

void setupSnake() { //run this at the start
  snake[0][0] = B00000000;
  snake[0][1] = B00000000;
  snake[0][2] = B00110100;
  snake[0][3] = B00000000;
  snake[0][4] = B00000000;
  snake[0][5] = B00000000;
  snake[0][6] = B00000000;
  snake[0][7] = B00000000;
  snake[1][0] = B00000000;
  snake[1][1] = B00000000;
  snake[1][2] = B00011100;
  snake[1][3] = B00000000;
  snake[1][4] = B00000000;
  snake[1][5] = B00000000;
  snake[1][6] = B00000000;
  snake[1][7] = B00000000;
  snake[2][0] = B00000000;
  snake[2][1] = B00000000;
  snake[2][2] = B00001100;
  snake[2][3] = B00000000;
  snake[2][4] = B00000000;
  snake[2][5] = B00000000;
  snake[2][6] = B00000000;
  snake[2][7] = B00000000;
  snake[3][0] = B00000000;
  snake[3][1] = B00000000;
  snake[3][2] = B00000100;
  snake[3][3] = B00000100;
  snake[3][4] = B00010000;
  snake[3][5] = B00000000;
  snake[3][6] = B00000000;
  snake[3][7] = B00000000;
  snake[4][0] = B00000000;
  snake[4][1] = B00000000;
  snake[4][2] = B00000000;
  snake[4][3] = B00000100;
  snake[4][4] = B00010100;
  snake[4][5] = B00000000;
  snake[4][6] = B00000000;
  snake[4][7] = B00000000;
  snake[5][0] = B00000000;
  snake[5][1] = B00000000;
  snake[5][2] = B00000000;
  snake[5][3] = B00000000;
  snake[5][4] = B00011100;
  snake[5][5] = B00000000;
  snake[5][6] = B00000000;
  snake[5][7] = B00000000;
  snake[6][0] = B00000000;
  snake[6][1] = B00000000;
  snake[6][2] = B00000000;
  snake[6][3] = B00000000;
  snake[6][4] = B00011000;
  snake[6][5] = B00000000;
  snake[6][6] = B00000000;
  snake[6][7] = B00000000;
  snake[7][0] = B00000000;
  snake[7][1] = B00000000;
  snake[7][2] = B00000000;
  snake[7][3] = B00000000;
  snake[7][4] = B00010000;
  snake[7][5] = B00010100;
  snake[7][6] = B00000000;
  snake[7][7] = B00000000;
  snake[8][0] = B00000000;
  snake[8][1] = B00000000;
  snake[8][2] = B00000000;
  snake[8][3] = B00000000;
  snake[8][4] = B00000000;
  snake[8][5] = B00011100;
  snake[8][6] = B00000000;
  snake[8][7] = B00000000;
  snake[9][0] = B00000000;
  snake[9][1] = B00000000;
  snake[9][2] = B00000000;
  snake[9][3] = B00000000;
  snake[9][4] = B00000000;
  snake[9][5] = B00001100;
  snake[9][6] = B00000000;
  snake[9][7] = B00000000;
  snake[10][0] = B00000000;
  snake[10][1] = B00000000;
  snake[10][2] = B00100000;
  snake[10][3] = B00000000;
  snake[10][4] = B00000100;
  snake[10][5] = B00000100;
  snake[10][6] = B00000000;
  snake[10][7] = B00000000;
  snake[11][0] = B00000000;
  snake[11][1] = B00000000;
  snake[11][2] = B00100000;
  snake[11][3] = B00000000;
  snake[11][4] = B00001100;
  snake[11][5] = B00000000;
  snake[11][6] = B00000000;
  snake[11][7] = B00000000;
  snake[12][0] = B00000000;
  snake[12][1] = B00000000;
  snake[12][2] = B00100000;
  snake[12][3] = B00000000;
  snake[12][4] = B00011000;
  snake[12][5] = B00000000;
  snake[12][6] = B00000000;
  snake[12][7] = B00000000;
  snake[13][0] = B00000000;
  snake[13][1] = B00000000;
  snake[13][2] = B00100000;
  snake[13][3] = B00000000;
  snake[13][4] = B00110000;
  snake[13][5] = B00000000;
  snake[13][6] = B00000000;
  snake[13][7] = B00000000;
  snake[14][0] = B00000000;
  snake[14][1] = B00000000;
  snake[14][2] = B00100000;
  snake[14][3] = B00100000;
  snake[14][4] = B00100000;
  snake[14][5] = B00000000;
  snake[14][6] = B00000000;
  snake[14][7] = B00000000;
  snake[15][0] = B00000000;
  snake[15][1] = B00000000;
  snake[15][2] = B00100000;
  snake[15][3] = B00100000;
  snake[15][4] = B00000000;
  snake[15][5] = B00000000;
  snake[15][6] = B00000000;
  snake[15][7] = B00000000;
}

void setupBreakout() { //run this at the start
  breakout[0][0] = B00000000;
  breakout[0][1] = B00000000;
  breakout[0][2] = B00111100;
  breakout[0][3] = B00000000;
  breakout[0][4] = B00100000;
  breakout[0][5] = B00110000;
  breakout[0][6] = B00000000;
  breakout[0][7] = B00000000;
  breakout[1][0] = B00000000;
  breakout[1][1] = B00000000;
  breakout[1][2] = B00111100;
  breakout[1][3] = B00010000;
  breakout[1][4] = B00000000;
  breakout[1][5] = B00011000;
  breakout[1][6] = B00000000;
  breakout[1][7] = B00000000;
  breakout[2][0] = B00000000;
  breakout[2][1] = B00000000;
  breakout[2][2] = B00101100;
  breakout[2][3] = B00000000;
  breakout[2][4] = B00001000;
  breakout[2][5] = B00001100;
  breakout[2][6] = B00000000;
  breakout[2][7] = B00000000;
  breakout[3][0] = B00000000;
  breakout[3][1] = B00000000;
  breakout[3][2] = B00101100;
  breakout[3][3] = B00000100;
  breakout[3][4] = B00000000;
  breakout[3][5] = B00011000;
  breakout[3][6] = B00000000;
  breakout[3][7] = B00000000;
  breakout[4][0] = B00000000;
  breakout[4][1] = B00000000;
  breakout[4][2] = B00101000;
  breakout[4][3] = B00000000;
  breakout[4][4] = B00001000;
  breakout[4][5] = B00001100;
  breakout[4][6] = B00000000;
  breakout[4][7] = B00000000;
  breakout[5][0] = B00000000;
  breakout[5][1] = B00000000;
  breakout[5][2] = B00101000;
  breakout[5][3] = B00010000;
  breakout[5][4] = B00000000;
  breakout[5][5] = B00011000;
  breakout[5][6] = B00000000;
  breakout[5][7] = B00000000;
  breakout[6][0] = B00000000;
  breakout[6][1] = B00000000;
  breakout[6][2] = B00001000;
  breakout[6][3] = B00000000;
  breakout[6][4] = B00001000;
  breakout[6][5] = B00001100;
  breakout[6][6] = B00000000;
  breakout[6][7] = B00000000;
  breakout[7][0] = B00000000;
  breakout[7][1] = B00000000;
  breakout[7][2] = B00001000;
  breakout[7][3] = B00000100;
  breakout[7][4] = B00000000;
  breakout[7][5] = B00011000;
  breakout[7][6] = B00000000;
  breakout[7][7] = B00000000;
  breakout[8][0] = B00000000;
  breakout[8][1] = B00000000;
  breakout[8][2] = B00000000;
  breakout[8][3] = B00000000;
  breakout[8][4] = B00001000;
  breakout[8][5] = B00011000;
  breakout[8][6] = B00000000;
  breakout[8][7] = B00000000;
  breakout[9][0] = B00000000;
  breakout[9][1] = B00000000;
  breakout[9][2] = B00000000;
  breakout[9][3] = B00010000;
  breakout[9][4] = B00000000;
  breakout[9][5] = B00110000;
  breakout[9][6] = B00000000;
  breakout[9][7] = B00000000;
  breakout[10][0] = B00000000;
  breakout[10][1] = B00000000;
  breakout[10][2] = B00100000;
  breakout[10][3] = B00000000;
  breakout[10][4] = B00000000;
  breakout[10][5] = B01100000;
  breakout[10][6] = B00000000;
  breakout[10][7] = B00000000;
  breakout[11][0] = B00000000;
  breakout[11][1] = B00000000;
  breakout[11][2] = B00000000;
  breakout[11][3] = B01000000;
  breakout[11][4] = B00000000;
  breakout[11][5] = B00110000;
  breakout[11][6] = B00000000;
  breakout[11][7] = B00000000;
  breakout[12][0] = B00000000;
  breakout[12][1] = B00000000;
  breakout[12][2] = B00000000;
  breakout[12][3] = B00000000;
  breakout[12][4] = B00100000;
  breakout[12][5] = B01100000;
  breakout[12][6] = B00000000;
  breakout[12][7] = B00000000;
}

void setupSimon() {
  simon[0][0] = B00000000; //up
  simon[0][1] = B00011000;
  simon[0][2] = B00111100;
  simon[0][3] = B01111110;
  simon[0][4] = B00011000;
  simon[0][5] = B00011000;
  simon[0][6] = B00011000;
  simon[0][7] = B00000000;
  simon[1][0] = B00000000; //blank
  simon[1][1] = B00000000;
  simon[1][2] = B00000000;
  simon[1][3] = B00000000;
  simon[1][4] = B00000000;
  simon[1][5] = B00000000;
  simon[1][6] = B00000000;
  simon[1][7] = B00000000;
  simon[2][0] = B00000000; //blank
  simon[2][1] = B00000000;
  simon[2][2] = B00000000;
  simon[2][3] = B00000000;
  simon[2][4] = B00000000;
  simon[2][5] = B00000000;
  simon[2][6] = B00000000;
  simon[2][7] = B00000000;
  simon[3][7] = B00000000; //down (aka up, but flipped)
  simon[3][6] = B00011000;
  simon[3][5] = B00111100;
  simon[3][4] = B01111110;
  simon[3][3] = B00011000;
  simon[3][2] = B00011000;
  simon[3][1] = B00011000;
  simon[3][0] = B00000000;
  simon[4][0] = B00000000; //blank
  simon[4][1] = B00000000;
  simon[4][2] = B00000000;
  simon[4][3] = B00000000;
  simon[4][4] = B00000000;
  simon[4][5] = B00000000;
  simon[4][6] = B00000000;
  simon[4][7] = B00000000;
  simon[5][0] = B00000000; //blank
  simon[5][1] = B00000000;
  simon[5][2] = B00000000;
  simon[5][3] = B00000000;
  simon[5][4] = B00000000;
  simon[5][5] = B00000000;
  simon[5][6] = B00000000;
  simon[5][7] = B00000000;
  simon[6][0] = B00000000; //blank
  simon[6][1] = B00000000;
  simon[6][2] = B00000000;
  simon[6][3] = B00000000;
  simon[6][4] = B00000000;
  simon[6][5] = B00000000;
  simon[6][6] = B00000000;
  simon[6][7] = B00000000;
  simon[7][0] = B00000000; //left
  simon[7][1] = B00010000;
  simon[7][2] = B00110000;
  simon[7][3] = B01111110;
  simon[7][4] = B01111110;
  simon[7][5] = B00110000;
  simon[7][6] = B00010000;
  simon[7][7] = B00000000;
  simon[8][0] = B00000000; //blank
  simon[8][1] = B00000000;
  simon[8][2] = B00000000;
  simon[8][3] = B00000000;
  simon[8][4] = B00000000;
  simon[8][5] = B00000000;
  simon[8][6] = B00000000;
  simon[8][7] = B00000000;
  simon[9][0] = B00000000; //blank
  simon[9][1] = B00000000;
  simon[9][2] = B00000000;
  simon[9][3] = B00000000;
  simon[9][4] = B00000000;
  simon[9][5] = B00000000;
  simon[9][6] = B00000000;
  simon[9][7] = B00000000;
  simon[10][0] = B00000000; //right (left but flipped)
  simon[10][1] = B00001000;
  simon[10][2] = B00001100;
  simon[10][3] = B01111110;
  simon[10][4] = B01111110;
  simon[10][5] = B00001100;
  simon[10][6] = B00001000;
  simon[10][7] = B00000000;
  simon[11][0] = B00000000; //blank
  simon[11][1] = B00000000;
  simon[11][2] = B00000000;
  simon[11][3] = B00000000;
  simon[11][4] = B00000000;
  simon[11][5] = B00000000;
  simon[11][6] = B00000000;
  simon[11][7] = B00000000;
  simon[12][0] = B00000000; //blank
  simon[12][1] = B00000000;
  simon[12][2] = B00000000;
  simon[12][3] = B00000000;
  simon[12][4] = B00000000;
  simon[12][5] = B00000000;
  simon[12][6] = B00000000;
  simon[12][7] = B00000000;
  simon[13][0] = B00000000; //up
  simon[13][1] = B00011000;
  simon[13][2] = B00111100;
  simon[13][3] = B01111110;
  simon[13][4] = B00011000;
  simon[13][5] = B00011000;
  simon[13][6] = B00011000;
  simon[13][7] = B00000000;
  simon[14][7] = B00000000; //down (aka up, but flipped)
  simon[14][6] = B00011000;
  simon[14][5] = B00111100;
  simon[14][4] = B01111110;
  simon[14][3] = B00011000;
  simon[14][2] = B00011000;
  simon[14][1] = B00011000;
  simon[14][0] = B00000000;
  simon[15][0] = B00000000; //right (left but flipped)
  simon[15][1] = B00001000;
  simon[15][2] = B00001100;
  simon[15][3] = B01111110;
  simon[15][4] = B01111110;
  simon[15][5] = B00001100;
  simon[15][6] = B00001000;
  simon[15][7] = B00000000;
  simon[16][0] = B00000000;
  simon[16][1] = B01100110;
  simon[16][2] = B00111100;
  simon[16][3] = B00011000;
  simon[16][4] = B00011000;
  simon[16][5] = B00111100;
  simon[16][6] = B01100110;
  simon[16][7] = B00000000;
  simon[17][0] = B00000000;
  simon[17][1] = B01100110;
  simon[17][2] = B00111100;
  simon[17][3] = B00011000;
  simon[17][4] = B00011000;
  simon[17][5] = B00111100;
  simon[17][6] = B01100110;
  simon[17][7] = B00000000;
  simon[18][0] = B00000000;
  simon[18][1] = B01100110;
  simon[18][2] = B00111100;
  simon[18][3] = B00011000;
  simon[18][4] = B00011000;
  simon[18][5] = B00111100;
  simon[18][6] = B01100110;
  simon[18][7] = B00000000;
  simon[19][0] = B00000000;
  simon[19][1] = B01100110;
  simon[19][2] = B00111100;
  simon[19][3] = B00011000;
  simon[19][4] = B00011000;
  simon[19][5] = B00111100;
  simon[19][6] = B01100110;
  simon[19][7] = B00000000;
}

void setupFlappy() { //run this at the start
  flappy[0][0] = B00000000;
  flappy[0][1] = B00000000;
  flappy[0][2] = B00100000;
  flappy[0][3] = B00000000;
  flappy[0][4] = B00000010;
  flappy[0][5] = B00000010;
  flappy[0][6] = B00000010;
  flappy[0][7] = B00000000;
  flappy[1][0] = B00000000;
  flappy[1][1] = B00100000;
  flappy[1][2] = B00000000;
  flappy[1][3] = B00000000;
  flappy[1][4] = B00000110;
  flappy[1][5] = B00000110;
  flappy[1][6] = B00000110;
  flappy[1][7] = B00000000;
  flappy[2][0] = B00000000;
  flappy[2][1] = B00000000;
  flappy[2][2] = B00100000;
  flappy[2][3] = B00000000;
  flappy[2][4] = B00001100;
  flappy[2][5] = B00001100;
  flappy[2][6] = B00001100;
  flappy[2][7] = B00000000;
  flappy[3][0] = B00000000;
  flappy[3][1] = B00000000;
  flappy[3][2] = B00000000;
  flappy[3][3] = B00100000;
  flappy[3][4] = B00011000;
  flappy[3][5] = B00011000;
  flappy[3][6] = B00011000;
  flappy[3][7] = B00000000;
  flappy[4][0] = B00000000;
  flappy[4][1] = B00000000;
  flappy[4][2] = B00100000;
  flappy[4][3] = B00000000;
  flappy[4][4] = B00110000;
  flappy[4][5] = B00110000;
  flappy[4][6] = B00110000;
  flappy[4][7] = B00000000;
  flappy[5][0] = B00000000;
  flappy[5][1] = B00100000;
  flappy[5][2] = B00000000;
  flappy[5][3] = B00000000;
  flappy[5][4] = B01100000;
  flappy[5][5] = B01100000;
  flappy[5][6] = B01100000;
  flappy[5][7] = B00000000;
  flappy[6][0] = B00000000;
  flappy[6][1] = B00000000;
  flappy[6][2] = B00100000;
  flappy[6][3] = B00000000;
  flappy[6][4] = B01000000;
  flappy[6][5] = B01000000;
  flappy[6][6] = B01000000;
  flappy[6][7] = B00000000;
  flappy[7][0] = B00000000;
  flappy[7][1] = B00000000;
  flappy[7][2] = B00000000;
  flappy[7][3] = B00100000;
  flappy[7][4] = B00000000;
  flappy[7][5] = B00000000;
  flappy[7][6] = B00000000;
  flappy[7][7] = B00000000;
}

