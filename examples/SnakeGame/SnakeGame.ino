/*
This is a hackable version of a classic mobile phone game - Snake!
We've made this game as an example. You can see how it works, 
hack it, change it, and break it. We've commented the code to help
you understand what each function and variable does. For example, 
try to change the growth factor of the snake, the speed, or whether
you can pass through walls!
*/

#include <Gamer.h>

Gamer gamer;

int isPlaying;

// Tweaking variables
int snakeGrowthFactor = 1;
boolean passThroughWalls = true;
int snakeSpeed = 180;

/* These two arrays store the snake's X/Y coordinates!
  Our snake has a maximum length of 64. If it were any
  bigger, it wouldn't fit in our screen! */
int snakeX[64];
int snakeY[64];
int snakeDirection;

// Stores the snake's length. This is also the score!
int snakeLength;

int appleX;
int appleY;

// Splash screen image
byte splashScreen[8] = {
  B00000000,
  B01111110,
  B01000000,
  B01111110,
  B00000010,
  B00000010,
  B01011110,
  B00000000
};

void setup() {
  gamer.begin();
  randomSeed(gamer.ldrValue());
}

void loop() {
  if (isPlaying) {
    gamer.clear();
    updateApple();
    drawApple();
    updateDirection();
    moveSnake();
    detectCollision();
    drawSnake();
    gamer.updateDisplay();
    delay(snakeSpeed);
  }
  else {
    showSplashScreen();
  }
}

/* ---------------------------------------------------------------
  Displays the game's splash screen. Press start and the game will
  start.
*/
void showSplashScreen() {
  if (gamer.isPressed(START)) {
    // begin!
    snakeDirection = DOWN;
    snakeLength = 1;
    snakeX[0] = 0;
    snakeY[0] = 0;
    generateApple();
    isPlaying = true;
  }
  else {
    gamer.printImage(splashScreen);
  }
}

/* ---------------------------------------------------------------
  It's game over baby! Shows the score, and takes us back
  to the splash screen.
*/
void gameOver() {
  gamer.printString("Game over");
  delay(100);
  gamer.printString("Score");
  delay(500);
  gamer.showScore(snakeLength);
  delay(500);
  isPlaying = false;
}
