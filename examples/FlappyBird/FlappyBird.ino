/*
This is a Flappy Bird game for the DIY Gamer Kit.
We've made this game as an example. You can see how it works, 
hack it, change it, and break it. We've commented the code to 
help you understand what each function and variable does. 
For example, try to change the wall thickness to make the 
game more difficult. Or make it easier by changing the flyingSpeed
of the bird!
*/

// Include Gamer library.
#include <Gamer.h>

// Create a copy of the Gamer library.
Gamer gamer;

// General
int score;
boolean isPlaying;

// Wall - related
int wallThickness = 2;
int gapSize = 3;
int currentWallPosition;
int gapPosition;

// Bird - related
int flyingSpeed = 150;
int birdX = 2;
int birdY;
int gravity = 1;

// Sound - related
int gameStartSongLength = 3;
int gameStartNotes[] = {160, 140, 120};
int gameOverSongLength = 4;
int gameOverNotes[] = {120, 140, 160, 190};
int wallNote = 200;

// Splash screen image
byte splashScreen[8] = {B11101110,
                        B10001001,
                        B10001001,
                        B11101111,
                        B10001001,
                        B10001001,
                        B10001110,
                        B00000000};


void setup() {
  gamer.begin();
  randomSeed(gamer.ldrValue());
}

void loop() {
  if(isPlaying) {
    gamer.clear();
    moveWall();
    drawWall();
    updateBird();
    detectCollision();
    recordScore();
    drawBird();
    gamer.updateDisplay();
    delay(flyingSpeed);
  }
  else {
    showSplashScreen();
  }
}

/* ---------------------------------------------------------------
 Updates the bird's position. If you press UP, it will move up.
 Otherwise, gravity will bring it down :)
 */
void updateBird() {
  /* 
   If the UP button is pressed, move the bird up. Otherwise, 
   move it down with gravity. Remember, the X axis' 0 is on the top
   of the screen. Therefore, when we move the bird up, we REDUCE birdY. 
   When gravity brings it down, away from the axis' origin, 
   we INCREASE birdY.
   */
  if(gamer.isPressed(UP)) {
    birdY--;
  }
  else {
    birdY = birdY + gravity;
  }

  // Detect if the bird is on the floor.
  if(birdY == 7) gameOver();
}

/* ---------------------------------------------------------------
 Draws the bird. Wherever it might be!
 */
void drawBird() {
  // Make sure the bird isn't off the screen.
  birdY = constrain(birdY, 0, 7);
  // Display the bird dot.
  gamer.display[birdX][birdY] = 1;
}

/* ---------------------------------------------------------------
 Moves the walls from right to left on the screen, with a constant
 speed. 
 */
void moveWall() {
  // If the wall is at the end of the screen, get a new wall going!
  if(currentWallPosition == 0 - wallThickness) {
    generateWall();
  }
  // Otherwise, move the wall. 
  else {
    currentWallPosition--;
  }
}

/* ---------------------------------------------------------------
 Places a new wall on the edge of the screen, ready to be moved.
 */
void generateWall() {
  // Set the wall to the right of the screen.
  currentWallPosition = 8;
  // Get a random gap in the wall.
  gapPosition = random(1, 7-gapSize);
}

/* ---------------------------------------------------------------
 Draws the walls at their current position
 */
void drawWall() {
  // Draw multiple walls, if we need to.
  for(int j=0; j<wallThickness; j++) {
    if(currentWallPosition+j >= 0 && currentWallPosition+j <= 7) {
      for(int i=0; i<8; i++) {
        // Draw the wall, but miss out the gap. 
        if(i > gapPosition + gapSize - 1 || i < gapPosition) {
          gamer.display[currentWallPosition+j][i] = 1;
        }
      }
    }
  }
}

/* ---------------------------------------------------------------
 Checks if the bird is on a wall. If there's a pixel on the 
 same position as the bird, it's game over!
 */
void detectCollision() {
  if(gamer.display[birdX][birdY] == 1) {
    gameOver();
  }
}

/* ---------------------------------------------------------------
 Keeps track of the score. If the bird is flying through a wall, 
 add one to the score, and make a sound!
 */
void recordScore() {
  if(birdX == currentWallPosition + wallThickness) {
    score++;
    gamer.playTone(wallNote);
  }
  else gamer.stopTone();
}

/* ---------------------------------------------------------------
 Shows an image when the game isn't being played.
 */
void showSplashScreen() {
  if(gamer.isPressed(START)) {
    
    // Play a tune before the game starts.
    for(int i=0; i<gameStartSongLength; i++) {
      gamer.playTone(gameStartNotes[i]);
      delay(100);
    }
    
    // Stop the sound!
    gamer.stopTone();
    
    isPlaying = true;
    generateWall();
    birdY = 2;
    score = 0;
  }
  else {
    gamer.printImage(splashScreen);
  }
}

/* ---------------------------------------------------------------
 Shows Game over, followed by the score. 
 */
void gameOver() {
  
  // Play the Game Over tune.
  for(int i=0; i<gameOverSongLength; i++) {
    gamer.playTone(gameOverNotes[i]);
    delay(100);
  }
  
  // Turn off sound.
  gamer.stopTone();
  
  // Display Game Over followed by the score.
  gamer.printString("Game over");
  delay(100);
  gamer.printString("Score");
  delay(500);
  gamer.showScore(score);
  delay(500);
  isPlaying = false;
}



