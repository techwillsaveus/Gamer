volatile int currentXBreakout = 5;
volatile int currentYBreakout = 5;
volatile int velocity[2] = {
  -1,-1};
volatile byte blocks[8][8];
volatile byte paddleX = 2;
volatile byte counter = 0;
volatile int origXV=-1;
volatile int origYV=-1;
volatile byte scoreBreakout = 0;

// NOTE TO SELF: The physics in this is still iffy.
// FIX IT!!!

byte framesBreakout[2][8]; //declare at top of code
void setupImages() { //run this at the start
  framesBreakout[0][0] = B00000000;
  framesBreakout[0][1] = B01100110;
  framesBreakout[0][2] = B01100110;
  framesBreakout[0][3] = B00000000;
  framesBreakout[0][4] = B01000010;
  framesBreakout[0][5] = B00111100;
  framesBreakout[0][6] = B00000000;
  framesBreakout[0][7] = B00000000;
  framesBreakout[1][0] = B00000000;
  framesBreakout[1][1] = B01100110;
  framesBreakout[1][2] = B01100110;
  framesBreakout[1][3] = B00000000;
  framesBreakout[1][4] = B00000000;
  framesBreakout[1][5] = B00111100;
  framesBreakout[1][6] = B01000010;
  framesBreakout[1][7] = B00000000;
}

void startBreakout(boolean resetIt) {
  for(int x=0;x<8;x++) {
    for(int y=0;y<4;y++) {
      blocks[x][y] = 1;
    }
  }
  if(!resetIt) {
    scoreBreakout++;
    gamer.clear();
    gamer.printImage(framesBreakout[0]);
    delay(500);
  } 
  else scoreBreakout=0;
  currentXBreakout=random(4,8);
  currentYBreakout=5;
  velocity[0]=-1;
  velocity[1]=-1;
}

void breakoutLoop() {
  if(counter>2) {
    for(int x=0;x<8;x++) {
      for(int y=0;y<8;y++) {
        gamer.display[x][y] = LOW;
      }
    }
  }
  for(int x=0;x<8;x++) {
    gamer.display[x][7]=LOW;
  }
  if(gamer.isHeld(LEFT)&&paddleX>0){
    paddleX--;
  } 
  else if(gamer.isHeld(RIGHT)&&paddleX<4) {
    paddleX++;
  }
  for(int a=0;a<4;a++) {
    if(paddleX+a<8) {
      gamer.display[paddleX+a][7]=HIGH;
    }
  }
  if(counter>2) {
    origXV = velocity[0];
    origYV = velocity[1];
    for(int x=0;x<8;x++) {
      for(int y=0;y<4;y++) {
        if(blocks[x][y] == 1) {
          gamer.display[x][y] = HIGH;
        }
      }
    }
    physics();
    for(int x=0;x<8;x++) {
      for(int y=0;y<8;y++) {
        if(blocks[x][y]==0) {
          if(x%2==0) {
            if(y%2==0) {
              if(x<7) {
                blocks[x+1][y]=0;
              } else {
                blocks[0][y]=0;
              }
            } 
            else {
              if(x>0) {
                blocks[x-1][y]=0;
              } else {
                blocks[7][y]=0;
              }
            }
          } 
          else {
            if(y%2==0) {
              if(x>0) {
                blocks[x-1][y]=0;
              } else {
                blocks[7][y]=0;
              }
            } 
            else {
              if(x<7) {
                blocks[x+1][y]=0;
              } else {
                blocks[0][y]=0;
              }
            }
          }
        }  
      }
    }
    for(int x=0;x<8;x++) {
      for(int y=0;y<4;y++) {
        if(blocks[x][y] == 0) {
          gamer.display[x][y] = LOW;
        }
      }
    }
    byte newX = currentXBreakout + velocity[0];
    byte newY = currentYBreakout + velocity[1];
    if(newX>-1 && newX<8) {
      if(newY>-1 && newY<8) {
      } 
      else {
        if(gamer.display[newX][currentYBreakout-velocity[1]]==LOW) {
          blocks[newX][currentYBreakout+velocity[1]]=0;
          velocity[1]*=-1;
        } 
        else {
          blocks[currentXBreakout+velocity[0]][currentYBreakout+velocity[1]]=0;
          velocity[1]*=-1;
          velocity[0]*=-1;
        }
      }
    } 
    else {
      if(gamer.display[currentXBreakout-velocity[0]][newY]==LOW) {
        blocks[currentXBreakout+velocity[0]][newY]=0;
        velocity[0]*=-1;
        if(newY<0 || newY>7) {
          if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout-velocity[1]]==LOW) {
            blocks[currentXBreakout-velocity[0]][currentYBreakout-velocity[1]]=0;
            velocity[1]*=-1;
          } 
        }
      } 
      else {
        for(int x=-1;x<2;x++) {
          for(int y=-1;y<2;y++) {
            blocks[currentXBreakout+x][currentYBreakout+y]=0;
          }
        }
        velocity[0]*=-1;
        velocity[1]*=-1;
      }
    }
    currentXBreakout = currentXBreakout+velocity[0];
    currentYBreakout = currentYBreakout+velocity[1];
    gamer.display[currentXBreakout][currentYBreakout] = HIGH;
    counter=0;
  } 
  else counter++;
  gamer.updateDisplay();
  if(currentYBreakout==7) { //if out of play, lose
    for(int b=0;b<4;b++) {
      gamer.clear();
      delay(150);
      gamer.display[currentXBreakout][currentYBreakout]=HIGH;
      gamer.updateDisplay();
      delay(150);
    }
    if(scoreBreakout==0){
      gamer.clear();
      gamer.printImage(framesBreakout[1]);
    } 
    else if(scoreBreakout<10){
      gamer.clear();
      showScore(0,scoreBreakout);
    } 
    else {
      int dig2 = scoreBreakout % 10;  //split scoreBreakout into two digits (eg 10 -> 1 and 0)
      int dig1 = (scoreBreakout-(scoreBreakout%10))/10;
      gamer.clear();
      showScore(dig1,dig2);
    }
    delay(500);
    startBreakout(true);
  }
  boolean finished = true;
  for(int x=0;x<8;x++) {
    for(int y=0;y<4;y++) {
      if(blocks[x][y]==HIGH) finished=false;
    }
  }
  if(finished) {
    startBreakout(false);
  }
  delay(50);
}
 
boolean outOfBounds(int xV, int yV) {
  if(xV > 8 || xV < 0) {
    return true;
  } 
  else if(yV > 8 || yV < 0) {
    return true;
  } 
  else {
    return false;
  }
}
 
void physics() {
  if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout+velocity[1]]==HIGH || outOfBounds(currentXBreakout+velocity[0],currentYBreakout+velocity[1])) {
    //Collided with something!!!
    if(velocity[0]==1) {
      if(velocity[1]==1) {
        if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout-1]==LOW && !outOfBounds(currentXBreakout+velocity[0],currentYBreakout-1)) {
          velocity[1]=-1;
        }
        else if(gamer.display[currentXBreakout-1][currentYBreakout-1]==LOW && !outOfBounds(currentXBreakout-1,currentYBreakout-1)) {
          velocity[1]=-1;
          velocity[0]=-1;
        }
      }
      else if(velocity[1]==-1) {
        if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout+1]==LOW && !outOfBounds(currentXBreakout+velocity[0],currentYBreakout+1)) {
          velocity[1]=1;
        } 
        else if(gamer.display[currentXBreakout-1][currentYBreakout+1]==LOW && !outOfBounds(currentXBreakout-1,currentYBreakout+1)) {
          velocity[1]=1;
          velocity[0]=-1;
        } 
      } 
    } 
    else if(velocity[0]==-1) {
      if(velocity[1]==1) {
        if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout-1]==LOW && !outOfBounds(currentXBreakout+velocity[0],currentYBreakout-1)) {
          velocity[1]=-1;
        } 
        else if(gamer.display[currentXBreakout+1][currentYBreakout-1]==LOW && !outOfBounds(currentXBreakout-1,currentYBreakout-1)) {
          velocity[1]=-1;
          velocity[0]=1;
        }
      } 
      else if(velocity[1]==-1) {
        if(gamer.display[currentXBreakout+velocity[0]][currentYBreakout+1]==LOW && !outOfBounds(currentXBreakout+velocity[0],currentYBreakout+1)) {
          velocity[1]=1;
        } 
        else if(gamer.display[currentXBreakout+1][currentYBreakout+1]==LOW && !outOfBounds(currentXBreakout-1,currentYBreakout+1)) {
          velocity[1]=1;
          velocity[0]=1;
        }
      } 
    }
    if(!outOfBounds(currentXBreakout+origXV,currentYBreakout+origYV)) {
      blocks[currentXBreakout+origXV][currentYBreakout+origYV]=0;
    }
  }
}
