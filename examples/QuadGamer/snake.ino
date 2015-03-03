int currentX = 0;
int currentY = 0;
int dir = 1;
byte goalX = random(0,7);
byte goalY = random(0,7);
volatile byte snakeMap[8][8];
byte snakeLength = 2;
byte frames[11][8];
int score = 0;

void setupSnakeGame() {
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

void snakeLoop() {
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
  delay(100);
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
          //printString("GAME OVER  you scored",40);
          byte dig2 = score % 10;  //split score into two digits (eg 10 -> 1 and 0)
          byte dig1 = (score-(score%10))/10;
          showScore(dig1,dig2);
          delay(300);
          setupSnakeGame();
        }
      }
    }
  }
}
