/**
*   Flappy Bit Version 1.0
*   Original Arduino code By Daniel Ratcliffe http://www.twitter.com/DanTwoHundred
*   Text rendering code by Finnbar Keating
*   Adapted for the DIYGamer by George Profenza for TWSU
*/
#include <Gamer.h>

Gamer gamer;
 
// STATE
boolean menu = true;
boolean gameOver = false;
boolean displayScore = false;
//text rendering
byte letters[53][8];
byte numbers[10][2][8];
byte n1[8],n1b[8],n2[8],n2b[8],n3[8],n3b[8],n4[8],n4b[8],n5[8],n5b[8],n6[8],n6b[8],n7[8],n7b[8],n8[8],n8b[8],n9[8],n9b[8],n0[8],n0b[8];

int birdPos = 2;
int pipePos = 8;
int pipeGap = 3;
int ticks = 0;
int score = 0;
int inGameScreen[] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

int menuScreen[] = {
  0,0,0,1,1,0,0,0,
  0,0,1,0,0,1,0,0,
  0,0,1,0,1,1,0,0,
  1,1,1,0,0,1,0,0,
  1,0,0,1,1,1,1,0,
  1,0,1,0,1,0,0,1,
  0,1,0,0,1,1,1,0,
  0,0,1,1,1,0,0,0,
};


// UTILITY
void drawInGameScreen( int colour )
{  
  if( birdPos >= 0 && birdPos < 8 )
  {
    if( !gameOver || (gameOver && ((ticks / 24) % 2) == 1) )
    {
      inGameScreen[ 1 + birdPos*8 ] = colour;
    }
  }
  for( int y=0; y<8; ++y )
  {
    if( y < pipeGap || y >= pipeGap + 3 )
    {
      if( pipePos >= 0 && pipePos < 8 )
      {
        inGameScreen[ pipePos + y*8 ] = colour;
      }
      if( pipePos >= -1 && pipePos < 7 )
      {
        inGameScreen[ pipePos + 1 + y*8 ] = colour;
      }
    }
  }
}

// MAIN
void setup()
{             
  gamer.begin();
  setupScore();
}
void reset(){
  score = 0;
  displayScore = false;
  ticks = 0;
  birdPos = 2;
  pipePos = 20;
  pipeGap = 3;
  gameOver = false;
  drawInGameScreen( 1 );
}
void loop() 
{  
  // Update
  if( menu )
  {
    // IN MENU
    ++ticks;
    if( (ticks % 12) == 0 )
    {
      // Animate the eye
      if( rand()%30 == 0 ) 
      {
        menuScreen[ 19 ] = 1;
        menuScreen[ 20 ] = 0;
      }else
      {
        menuScreen[ 19 ] = 0;
        menuScreen[ 20 ] = 1;
      }
    }

    if(gamer.isPressed(START)) {
      menu = false;  
      reset();
    }
  }else if(displayScore){
    gamer.clear();
    int dig2 = score % 10;  //split score into two digits (eg 10 -> 1 and 0)
    int dig1 = (score-dig2)/10;
    showScore(dig1,dig2);
    delay(1000);
    displayScore = false;
    for(int i = 0 ; i < 64; i++) inGameScreen[i] = 0;
    reset();
    menu = true;
  }else{
    // IN GAME
    // Clear the screen
    drawInGameScreen( 0 );
    
    // Update the state
    ++ticks;
    if( !gameOver && ((ticks % 12) == 0) )
    {
      // Move the pipe
      int lastPipePos = pipePos;
      pipePos--;
      if( pipePos < -1 )
      {
        score++;
        pipePos = 7; 
        pipeGap = 1 + rand()%4;
      }
           
      // Move the bird
      int lastBirdPos = birdPos;
      if(gamer.isPressed(UP)) birdPos = max( birdPos - 1, 0 );//move the bird upwards when UP key is pressed
      else{
        birdPos++;//move the bird down
        if( birdPos >= 8 )//check if the bird hit the ground
        {
          gameOver = true;
          pipePos = lastPipePos;
          birdPos = lastBirdPos;
          ticks = 0;
        }
      }
      
      // Test for pipe collision
      if( (pipePos == 1 || pipePos == 0) && (birdPos < pipeGap || birdPos >= pipeGap + 3) )
      {
        gameOver = true;
        pipePos = lastPipePos;
        birdPos = lastBirdPos;
        ticks = 0;
      }
//    }else if( gameOver && ticks >= 96 ) menu = true;//game over, display the last position for 96 ticks then return to menu
    }else if( gameOver && ticks >= 96 ) displayScore = true;//game over, display the last position for 96 ticks then return to menu
    if( !menu ) drawInGameScreen( 1 ); // Redraw the screen
  }
  
  // Render
  if(!displayScore){
    int* screen = menu ? menuScreen : inGameScreen;
    for(int i = 0 ; i < 64; i++){
      int x = i%8;
      int y = i/8;
      gamer.display[x][y] = screen[i];
    }
    gamer.updateDisplay();
  }
  delay(12);
}
