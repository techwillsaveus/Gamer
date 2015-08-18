/*
 * These are all apple-related functions.
 */

/* ---------------------------------------------------------------
  Checks if the apple has been eaten by the snake. If it has, 
  it makes the snake longer and generates a new apple. 
*/
void updateApple() {
  if(snakeX[0] == appleX && snakeY[0] == appleY) {
    generateApple();
    snakeLength = snakeLength + snakeGrowthFactor;
  }
}

/* ---------------------------------------------------------------
  Generates a new apple, at a random position on the screen.
*/
void generateApple() {
  appleX = random(0, 7);
  appleY = random(0, 7);
}

/* ---------------------------------------------------------------
  Draws the apple on the screen. 
*/
void drawApple() {
  gamer.display[appleX][appleY] = 1;
}
