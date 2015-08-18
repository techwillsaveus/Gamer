/* ---------------------------------------------------------------
 Checks to see if buttons are pressed, then changes the direction
 of the snake.
 */
void updateDirection() {
  if(gamer.isPressed(UP)) {
    if(snakeDirection != DOWN) snakeDirection = UP;
  }
  else if(gamer.isPressed(DOWN)) {
    if(snakeDirection != UP) snakeDirection = DOWN;
  }
  else if(gamer.isPressed(LEFT)) {
    if(snakeDirection != RIGHT) snakeDirection = LEFT;
  }
  else if(gamer.isPressed(RIGHT)) {
    if(snakeDirection != LEFT) snakeDirection = RIGHT;
  }
}

/* ---------------------------------------------------------------
 Moves the snake's head by one position forward, depending on the snake's
 direction. 
 */
void moveSnake() {
  int newX;
  int newY;
  
  // Change the head's position, depending
  // on the direction the snake is going towards.
  if(snakeDirection == LEFT) {
    newX = snakeX[0] - 1;
    newY = snakeY[0];
  }
  else if(snakeDirection == RIGHT) {
    newX = snakeX[0] + 1;
    newY = snakeY[0];
  }
  else if(snakeDirection == UP) {
    newX = snakeX[0];
    newY = snakeY[0] - 1;
  }
  else if(snakeDirection == DOWN) {
    newX = snakeX[0];
    newY = snakeY[0] + 1;
  }
  
  moveBody();
  
  /* Store the snake's new head position. 
  If it's off the screen, put it back into 
  the screen! */
  if(passThroughWalls == true) {
    if(newX == 8) snakeX[0] = 0;
    else if(newX == -1) snakeX[0] = 7;
    else snakeX[0] = newX;
    
    if(newY == 8) snakeY[0] = 0;
    else if(newY == -1) snakeY[0] = 7;
    else snakeY[0] = newY;
  }
  else if(passThroughWalls == false) {
    if(newX == 8 || newX == -1) gameOver();
    else snakeX[0] = newX;

    if(newY == 8 || newY == -1) gameOver();
    else snakeY[0] = newY;
  }
}

/* ---------------------------------------------------------------
 Moves the snake's body to follow the head.
 */
void moveBody() {
  // Move the rest of the snake forward!
  for(int i=snakeLength-1; i>0; i--) {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
}

/* ---------------------------------------------------------------
 Checks whether the snake has crashed into itself.
 */
void detectCollision() {
  for(int i=1; i<snakeLength; i++) {
    if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) gameOver();
  }
}

/* ---------------------------------------------------------------
 Draws the snake on the screen.
 */
void drawSnake() {
  for(int i=0; i<snakeLength; i++) {
    gamer.display[snakeX[i]][snakeY[i]] = 1;
  }
}
