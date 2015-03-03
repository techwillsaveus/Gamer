/*
Due to memory problems and the fact that it is the largest memory cost of a
function that is used once, printString has been removed. Sorry.
*/

//volatile byte letters[53][8];
volatile byte numbers[10][2][8];
//volatile boolean printing = true;
//volatile boolean doit = true;
//volatile int shift1 = -8;
//volatile int shift2 = -16;
//volatile byte i = 0;
//volatile byte i2= 1;

//void printString(String string, int delayMs) {
//  gamer.clear();
//  byte iter = 0;
//  //otherwise, string -> binary letters works perfectly!
//  byte len = string.length();
//  len++;
//  byte lettersToPrint[len][8];
//  byte stringBytes[len];
//  int stringArray[len];
//  string.getBytes(stringBytes,len);
//  for(int a=0;a<len;a++) {
//    if(stringBytes[a] > 96) {
//      stringArray[a] = stringBytes[a] - 70; //from 97-122 to 27-52
//    }
//    else if(stringBytes[a] > 64) { //from 65-90 to 1-26
//      stringArray[a] = stringBytes[a] - 64;
//    }
//    else if(stringBytes[a] == 32) { //32 becomes 0
//      stringArray[a] = 0;
//    }
//    else {
//      stringArray[a] = 9000; //just to identify unuseable strings
//    }
//    //Serial.println(stringArray[a]);
//  }
//  for(int a=0;a<len;a++) {
//    for(int b=0;b<8;b++) {
//      if(stringArray[a] < 9000) {
//        lettersToPrint[a][b] = letters[stringArray[a]][b];
//        //Serial.println(lettersToPrint[a][b]);
//      }
//    }
//  } //letters are recorded perfectly into the array!
//  printing = true;
//  doit = true;
//  shift1 = -8;
//  shift2 = -16;
//  i = 0;
//  i2= 1;
//  while(printing) {
//    byte temp[8];
//    byte temp2[8];
//    byte result[8];
//    //Serial.println("printing!");
//    for(int r=0;r<8;r++) { //row
//      if(doit) { //true if NOT the last letter, otherwise...
//        if(shift1>0) { //for letter 1
//          temp[r] = lettersToPrint[i][r] << shift1; //work out how to shift it
//        }
//        else if(shift1<0) {
//          temp[r] = lettersToPrint[i][r] >> (shift1*-1);
//        }
//        else {
//          temp[r] = lettersToPrint[i][r]; //and store it as temp
//        }
//      }
//      else {
//        for(int p=0;p<8;p++) {
//          temp[p] = 0;
//        }
//      }
//      if(shift2>0) { //repeat for letter 2 (as they will be appearing on screen at the same time)
//        temp2[r] = lettersToPrint[i2][r] << shift2;
//      }
//      else if(shift2<0) {
//        temp2[r] = lettersToPrint[i2][r] >> (shift2*-1);
//      }
//      else {
//        temp2[r] = lettersToPrint[i2][r];
//      }
//      if(doit) {
//        result[r] = temp[r] ^ temp2[r]; //combine the two
//      }
//      else {
//        result[r] = temp2[r];
//      }
//    }
//    gamer.printImage(result); //and draw :D
//    if(gamer.isHeld(START)) break;
//    delay(delayMs);
//    if(gamer.isHeld(START)) break;
//    shift1++; //after 40 frames, increase the shift
//    shift2++; //for both
//    if(shift1>8) { //reset it when it reaches +8
//      shift1=-8;
//      i+=2; //and move TWO letters forward!
//    }
//    if(shift2>8) { //repeat
//      shift2=-8;
//      i2+=2;
//    }
//    if(i>len) doit = false; //stops the first char from being reprinted
//    if(i2>len) {
//      printing = false;
//    }
//    iter++;
//  }
//}

void showScore(byte dig1,byte dig2) {
  byte result[8];
  for(int p=0;p<8;p++) {
    result[p]=numbers[dig1][0][p]^numbers[dig2][1][p];
  }
  gamer.printImage(result);
}

void setupScore() {
  numbers[1][0][0] = B10000000;
  numbers[1][0][1] = B10000000;
  numbers[1][0][2] = B10000000;
  numbers[1][0][3] = B10000000;
  numbers[1][0][4] = B10000000;
  numbers[1][0][5] = B10000000;
  numbers[1][0][6] = B10000000;
  numbers[1][0][7] = B10000000;

  numbers[1][1][0] = B00000100;
  numbers[1][1][1] = B00000100;
  numbers[1][1][2] = B00000100;
  numbers[1][1][3] = B00000100;
  numbers[1][1][4] = B00000100;
  numbers[1][1][5] = B00000100;
  numbers[1][1][6] = B00000100;
  numbers[1][1][7] = B00000100;

  numbers[2][0][0] = B11100000;
  numbers[2][0][1] = B00100000;
  numbers[2][0][2] = B00100000;
  numbers[2][0][3] = B11100000;
  numbers[2][0][4] = B10000000;
  numbers[2][0][5] = B10000000;
  numbers[2][0][6] = B10000000;
  numbers[2][0][7] = B11100000;

  numbers[2][1][0] = B00000111;
  numbers[2][1][1] = B00000001;
  numbers[2][1][2] = B00000001;
  numbers[2][1][3] = B00000111;
  numbers[2][1][4] = B00000100;
  numbers[2][1][5] = B00000100;
  numbers[2][1][6] = B00000100;
  numbers[2][1][7] = B00000111;

  numbers[3][0][0] = B11100000;
  numbers[3][0][1] = B00100000;
  numbers[3][0][2] = B00100000;
  numbers[3][0][3] = B01100000;
  numbers[3][0][4] = B00100000;
  numbers[3][0][5] = B00100000;
  numbers[3][0][6] = B00100000;
  numbers[3][0][7] = B11100000;

  numbers[3][1][0] = B00000111;
  numbers[3][1][1] = B00000001;
  numbers[3][1][2] = B00000001;
  numbers[3][1][3] = B00000011;
  numbers[3][1][4] = B00000001;
  numbers[3][1][5] = B00000001;
  numbers[3][1][6] = B00000001;
  numbers[3][1][7] = B00000111;

  numbers[4][0][0] = B10100000;
  numbers[4][0][1] = B10100000;
  numbers[4][0][2] = B10100000;
  numbers[4][0][3] = B11100000;
  numbers[4][0][4] = B00100000;
  numbers[4][0][5] = B00100000;
  numbers[4][0][6] = B00100000;
  numbers[4][0][7] = B00100000;

  numbers[4][1][0] = B00000101;
  numbers[4][1][1] = B00000101;
  numbers[4][1][2] = B00000101;
  numbers[4][1][3] = B00000111;
  numbers[4][1][4] = B00000001;
  numbers[4][1][5] = B00000001;
  numbers[4][1][6] = B00000001;
  numbers[4][1][7] = B00000001;

  numbers[5][0][0] = B11100000;
  numbers[5][0][1] = B10000000;
  numbers[5][0][2] = B10000000;
  numbers[5][0][3] = B11100000;
  numbers[5][0][4] = B00100000;
  numbers[5][0][5] = B00100000;
  numbers[5][0][6] = B00100000;
  numbers[5][0][7] = B11100000;

  numbers[5][1][0] = B00000111;
  numbers[5][1][1] = B00000100;
  numbers[5][1][2] = B00000100;
  numbers[5][1][3] = B00000111;
  numbers[5][1][4] = B00000001;
  numbers[5][1][5] = B00000001;
  numbers[5][1][6] = B00000001;
  numbers[5][1][7] = B00000111;

  numbers[6][0][0] = B11100000;
  numbers[6][0][1] = B10000000;
  numbers[6][0][2] = B10000000;
  numbers[6][0][3] = B11100000;
  numbers[6][0][4] = B10100000;
  numbers[6][0][5] = B10100000;
  numbers[6][0][6] = B10100000;
  numbers[6][0][7] = B11100000;

  numbers[6][1][0] = B00000111;
  numbers[6][1][1] = B00000100;
  numbers[6][1][2] = B00000100;
  numbers[6][1][3] = B00000111;
  numbers[6][1][4] = B00000101;
  numbers[6][1][5] = B00000101;
  numbers[6][1][6] = B00000101;
  numbers[6][1][7] = B00000111;

  numbers[7][0][0] = B11100000;
  numbers[7][0][1] = B00100000;
  numbers[7][0][2] = B00100000;
  numbers[7][0][3] = B00100000;
  numbers[7][0][4] = B00100000;
  numbers[7][0][5] = B00100000;
  numbers[7][0][6] = B00100000;
  numbers[7][0][7] = B00100000;

  numbers[7][1][0] = B00000111;
  numbers[7][1][1] = B00000001;
  numbers[7][1][2] = B00000001;
  numbers[7][1][3] = B00000001;
  numbers[7][1][4] = B00000001;
  numbers[7][1][5] = B00000001;
  numbers[7][1][6] = B00000001;
  numbers[7][1][7] = B00000001;

  numbers[8][0][0] = B11100000;
  numbers[8][0][1] = B10100000;
  numbers[8][0][2] = B10100000;
  numbers[8][0][3] = B11100000;
  numbers[8][0][4] = B10100000;
  numbers[8][0][5] = B10100000;
  numbers[8][0][6] = B10100000;
  numbers[8][0][7] = B11100000;

  numbers[8][1][0] = B00000111;
  numbers[8][1][1] = B00000101;
  numbers[8][1][2] = B00000101;
  numbers[8][1][3] = B00000111;
  numbers[8][1][4] = B00000101;
  numbers[8][1][5] = B00000101;
  numbers[8][1][6] = B00000101;
  numbers[8][1][7] = B00000111;

  numbers[9][0][0] = B11100000;
  numbers[9][0][1] = B10100000;
  numbers[9][0][2] = B10100000;
  numbers[9][0][3] = B11100000;
  numbers[9][0][4] = B00100000;
  numbers[9][0][5] = B00100000;
  numbers[9][0][6] = B00100000;
  numbers[9][0][7] = B11100000;

  numbers[9][1][0] = B00000111;
  numbers[9][1][1] = B00000101;
  numbers[9][1][2] = B00000101;
  numbers[9][1][3] = B00000111;
  numbers[9][1][4] = B00000001;
  numbers[9][1][5] = B00000001;
  numbers[9][1][6] = B00000001;
  numbers[9][1][7] = B00000111;

  numbers[0][0][0] = B11100000;
  numbers[0][0][1] = B10100000;
  numbers[0][0][2] = B10100000;
  numbers[0][0][3] = B10100000;
  numbers[0][0][4] = B10100000;
  numbers[0][0][5] = B10100000;
  numbers[0][0][6] = B10100000;
  numbers[0][0][7] = B11100000;

  numbers[0][1][0] = B00000111;
  numbers[0][1][1] = B00000101;
  numbers[0][1][2] = B00000101;
  numbers[0][1][3] = B00000101;
  numbers[0][1][4] = B00000101;
  numbers[0][1][5] = B00000101;
  numbers[0][1][6] = B00000101;
  numbers[0][1][7] = B00000111;

//  letters[0][0] = B00000000;
//  letters[0][1] = B00000000;
//  letters[0][2] = B00000000;
//  letters[0][3] = B00000000;
//  letters[0][4] = B00000000;
//  letters[0][5] = B00000000;
//  letters[0][6] = B00000000;
//  letters[0][7] = B00000000;
//  letters[1][0] = B00000000;
//  letters[1][1] = B00111000;
//  letters[1][2] = B01000100;
//  letters[1][3] = B01000100;
//  letters[1][4] = B01111100;
//  letters[1][5] = B01000100;
//  letters[1][6] = B01000100;
//  letters[1][7] = B01000100;
//  letters[2][0] = B00000000;
//  letters[2][1] = B01111000;
//  letters[2][2] = B01000100;
//  letters[2][3] = B01000100;
//  letters[2][4] = B01111100;
//  letters[2][5] = B01000100;
//  letters[2][6] = B01000100;
//  letters[2][7] = B01111000;
//  letters[3][0] = B00000000;
//  letters[3][1] = B00111100;
//  letters[3][2] = B01000000;
//  letters[3][3] = B01000000;
//  letters[3][4] = B01000000;
//  letters[3][5] = B01000000;
//  letters[3][6] = B01000000;
//  letters[3][7] = B00111100;
//  letters[4][0] = B00000000;
//  letters[4][1] = B01111000;
//  letters[4][2] = B01000100;
//  letters[4][3] = B01000100;
//  letters[4][4] = B01000100;
//  letters[4][5] = B01000100;
//  letters[4][6] = B01000100;
//  letters[4][7] = B01111000;
//  letters[5][0] = B00000000;
//  letters[5][1] = B01111100;
//  letters[5][2] = B01000000;
//  letters[5][3] = B01000000;
//  letters[5][4] = B01111000;
//  letters[5][5] = B01000000;
//  letters[5][6] = B01000000;
//  letters[5][7] = B01111100;
//  letters[6][0] = B00000000;
//  letters[6][1] = B00111100;
//  letters[6][2] = B01000000;
//  letters[6][3] = B01000000;
//  letters[6][4] = B01111000;
//  letters[6][5] = B01000000;
//  letters[6][6] = B01000000;
//  letters[6][7] = B01000000;
//  letters[7][0] = B00000000;
//  letters[7][1] = B00111100;
//  letters[7][2] = B01000000;
//  letters[7][3] = B01000000;
//  letters[7][4] = B01000000;
//  letters[7][5] = B01000100;
//  letters[7][6] = B00111100;
//  letters[7][7] = B00000100;
//  letters[8][0] = B00000000;
//  letters[8][1] = B01000100;
//  letters[8][2] = B01000100;
//  letters[8][3] = B01000100;
//  letters[8][4] = B01111100;
//  letters[8][5] = B01000100;
//  letters[8][6] = B01000100;
//  letters[8][7] = B01000100;
//  letters[9][0] = B00000000;
//  letters[9][1] = B01111100;
//  letters[9][2] = B00010000;
//  letters[9][3] = B00010000;
//  letters[9][4] = B00010000;
//  letters[9][5] = B00010000;
//  letters[9][6] = B00010000;
//  letters[9][7] = B01111100;
//  letters[10][0] = B00000000;
//  letters[10][1] = B01111100;
//  letters[10][2] = B00010000;
//  letters[10][3] = B00010000;
//  letters[10][4] = B00010000;
//  letters[10][5] = B00010000;
//  letters[10][6] = B00010000;
//  letters[10][7] = B01100000;
//  letters[11][0] = B00000000;
//  letters[11][1] = B01000100;
//  letters[11][2] = B01001000;
//  letters[11][3] = B01010000;
//  letters[11][4] = B01100000;
//  letters[11][5] = B01010000;
//  letters[11][6] = B01001000;
//  letters[11][7] = B01000100;
//  letters[12][0] = B00000000;
//  letters[12][1] = B01000000;
//  letters[12][2] = B01000000;
//  letters[12][3] = B01000000;
//  letters[12][4] = B01000000;
//  letters[12][5] = B01000000;
//  letters[12][6] = B01000000;
//  letters[12][7] = B01111100;
//  letters[13][0] = B00000000;
//  letters[13][1] = B01000100;
//  letters[13][2] = B01101100;
//  letters[13][3] = B01010100;
//  letters[13][4] = B01000100;
//  letters[13][5] = B01000100;
//  letters[13][6] = B01000100;
//  letters[13][7] = B01000100;
//  letters[14][0] = B00000000;
//  letters[14][1] = B01000100;
//  letters[14][2] = B01100100;
//  letters[14][3] = B01100100;
//  letters[14][4] = B01110100;
//  letters[14][5] = B01011100;
//  letters[14][6] = B01001100;
//  letters[14][7] = B01000100;
//  letters[15][0] = B00000000;
//  letters[15][1] = B00111000;
//  letters[15][2] = B01000100;
//  letters[15][3] = B01000100;
//  letters[15][4] = B01000100;
//  letters[15][5] = B01000100;
//  letters[15][6] = B01000100;
//  letters[15][7] = B00111000;
//  letters[16][0] = B00000000;
//  letters[16][1] = B00111000;
//  letters[16][2] = B01000100;
//  letters[16][3] = B01000100;
//  letters[16][4] = B01111000;
//  letters[16][5] = B01000000;
//  letters[16][6] = B01000000;
//  letters[16][7] = B01000000;
//  letters[17][0] = B00000000;
//  letters[17][1] = B00111000;
//  letters[17][2] = B01000100;
//  letters[17][3] = B01000100;
//  letters[17][4] = B01010100;
//  letters[17][5] = B00111000;
//  letters[17][6] = B00010000;
//  letters[17][7] = B00000000;
//  letters[18][0] = B00000000;
//  letters[18][1] = B01111000;
//  letters[18][2] = B01000100;
//  letters[18][3] = B01000100;
//  letters[18][4] = B01111100;
//  letters[18][5] = B01100000;
//  letters[18][6] = B01010000;
//  letters[18][7] = B01001000;
//  letters[19][0] = B00000000;
//  letters[19][1] = B00111100;
//  letters[19][2] = B01000000;
//  letters[19][3] = B01000000;
//  letters[19][4] = B00111000;
//  letters[19][5] = B00000100;
//  letters[19][6] = B00000100;
//  letters[19][7] = B01111000;
//  letters[20][0] = B00000000;
//  letters[20][1] = B01111100;
//  letters[20][2] = B00010000;
//  letters[20][3] = B00010000;
//  letters[20][4] = B00010000;
//  letters[20][5] = B00010000;
//  letters[20][6] = B00010000;
//  letters[20][7] = B00010000;
//  letters[21][0] = B00000000;
//  letters[21][1] = B01000100;
//  letters[21][2] = B01000100;
//  letters[21][3] = B01000100;
//  letters[21][4] = B01000100;
//  letters[21][5] = B01000100;
//  letters[21][6] = B01000100;
//  letters[21][7] = B01111100;
//  letters[22][0] = B00000000;
//  letters[22][1] = B01000100;
//  letters[22][2] = B01000100;
//  letters[22][3] = B01000100;
//  letters[22][4] = B00101000;
//  letters[22][5] = B00101000;
//  letters[22][6] = B00010000;
//  letters[22][7] = B00010000;
//  letters[23][0] = B00000000;
//  letters[23][1] = B01000100;
//  letters[23][2] = B01000100;
//  letters[23][3] = B01000100;
//  letters[23][4] = B01010100;
//  letters[23][5] = B01010100;
//  letters[23][6] = B01010100;
//  letters[23][7] = B00101000;
//  letters[24][0] = B00000000;
//  letters[24][1] = B01000100;
//  letters[24][2] = B01000100;
//  letters[24][3] = B00101000;
//  letters[24][4] = B00101000;
//  letters[24][5] = B00010000;
//  letters[24][6] = B00101000;
//  letters[24][7] = B01000100;
//  letters[25][0] = B00000000;
//  letters[25][1] = B01000100;
//  letters[25][2] = B01000100;
//  letters[25][3] = B00101000;
//  letters[25][4] = B00010000;
//  letters[25][5] = B00010000;
//  letters[25][6] = B00010000;
//  letters[25][7] = B00010000;
//  letters[26][0] = B00000000;
//  letters[26][1] = B01111100;
//  letters[26][2] = B00000100;
//  letters[26][3] = B00001000;
//  letters[26][4] = B00010000;
//  letters[26][5] = B00100000;
//  letters[26][6] = B01000000;
//  letters[26][7] = B01111100;
//  letters[27][0] = B00000000;
//  letters[27][1] = B00000000;
//  letters[27][2] = B00000000;
//  letters[27][3] = B00111000;
//  letters[27][4] = B01000100;
//  letters[27][5] = B01000100;
//  letters[27][6] = B01000100;
//  letters[27][7] = B00111110;
//  letters[28][0] = B00100000;
//  letters[28][1] = B00100000;
//  letters[28][2] = B00100000;
//  letters[28][3] = B00100000;
//  letters[28][4] = B00111100;
//  letters[28][5] = B00100010;
//  letters[28][6] = B00100010;
//  letters[28][7] = B00111100;
//  letters[29][0] = B00000000;
//  letters[29][1] = B00000000;
//  letters[29][2] = B00000000;
//  letters[29][3] = B00000000;
//  letters[29][4] = B00111100;
//  letters[29][5] = B00100000;
//  letters[29][6] = B00100000;
//  letters[29][7] = B00111100;
//  letters[30][0] = B00000100;
//  letters[30][1] = B00000100;
//  letters[30][2] = B00000100;
//  letters[30][3] = B00000100;
//  letters[30][4] = B00111100;
//  letters[30][5] = B00100100;
//  letters[30][6] = B00100100;
//  letters[30][7] = B00111110;
//  letters[31][0] = B00000000;
//  letters[31][1] = B00000000;
//  letters[31][2] = B00000000;
//  letters[31][3] = B00111100;
//  letters[31][4] = B00100100;
//  letters[31][5] = B00111100;
//  letters[31][6] = B00100000;
//  letters[31][7] = B00111100;
//  letters[32][0] = B00011100;
//  letters[32][1] = B00100000;
//  letters[32][2] = B00100000;
//  letters[32][3] = B00100000;
//  letters[32][4] = B00111000;
//  letters[32][5] = B00100000;
//  letters[32][6] = B00100000;
//  letters[32][7] = B00100000;
//  letters[33][0] = B00011100;
//  letters[33][1] = B00010100;
//  letters[33][2] = B00011100;
//  letters[33][3] = B00000100;
//  letters[33][4] = B00000100;
//  letters[33][5] = B00000100;
//  letters[33][6] = B00000100;
//  letters[33][7] = B00011000;
//  letters[34][0] = B00010000;
//  letters[34][1] = B00010000;
//  letters[34][2] = B00010000;
//  letters[34][3] = B00010000;
//  letters[34][4] = B00011100;
//  letters[34][5] = B00010100;
//  letters[34][6] = B00010100;
//  letters[34][7] = B00010100;
//  letters[35][0] = B00000000;
//  letters[35][1] = B00000000;
//  letters[35][2] = B00010000;
//  letters[35][3] = B00000000;
//  letters[35][4] = B00010000;
//  letters[35][5] = B00010000;
//  letters[35][6] = B00010000;
//  letters[35][7] = B00010000;
//  letters[36][0] = B00001000;
//  letters[36][1] = B00000000;
//  letters[36][2] = B00001000;
//  letters[36][3] = B00001000;
//  letters[36][4] = B00001000;
//  letters[36][5] = B00001000;
//  letters[36][6] = B00001000;
//  letters[36][7] = B00110000;
//  letters[37][0] = B00100000;
//  letters[37][1] = B00100000;
//  letters[37][2] = B00100100;
//  letters[37][3] = B00101000;
//  letters[37][4] = B00110000;
//  letters[37][5] = B00110000;
//  letters[37][6] = B00101000;
//  letters[37][7] = B00100100;
//  letters[38][0] = B00010000;
//  letters[38][1] = B00010000;
//  letters[38][2] = B00010000;
//  letters[38][3] = B00010000;
//  letters[38][4] = B00010000;
//  letters[38][5] = B00010000;
//  letters[38][6] = B00010000;
//  letters[38][7] = B00001100;
//  letters[39][0] = B00000000;
//  letters[39][1] = B00000000;
//  letters[39][2] = B00000000;
//  letters[39][3] = B00110110;
//  letters[39][4] = B01001001;
//  letters[39][5] = B01001001;
//  letters[39][6] = B01000001;
//  letters[39][7] = B01000001;
//  letters[40][0] = B00000000;
//  letters[40][1] = B00000000;
//  letters[40][2] = B00000000;
//  letters[40][3] = B00000000;
//  letters[40][4] = B00110000;
//  letters[40][5] = B01001000;
//  letters[40][6] = B01001000;
//  letters[40][7] = B01001000;
//  letters[41][0] = B00000000;
//  letters[41][1] = B00000000;
//  letters[41][2] = B00000000;
//  letters[41][3] = B00000000;
//  letters[41][4] = B00110000;
//  letters[41][5] = B01001000;
//  letters[41][6] = B01001000;
//  letters[41][7] = B00110000;
//  letters[42][0] = B00000000;
//  letters[42][1] = B00000000;
//  letters[42][2] = B00110000;
//  letters[42][3] = B01001000;
//  letters[42][4] = B01001000;
//  letters[42][5] = B01110000;
//  letters[42][6] = B01000000;
//  letters[42][7] = B01000000;
//  letters[43][0] = B00011000;
//  letters[43][1] = B00100100;
//  letters[43][2] = B00100100;
//  letters[43][3] = B00011100;
//  letters[43][4] = B00000100;
//  letters[43][5] = B00000101;
//  letters[43][6] = B00000110;
//  letters[43][7] = B00000100;
//  letters[44][0] = B00000000;
//  letters[44][1] = B00000000;
//  letters[44][2] = B00000000;
//  letters[44][3] = B00000000;
//  letters[44][4] = B00101100;
//  letters[44][5] = B00110000;
//  letters[44][6] = B00100000;
//  letters[44][7] = B00100000;
//  letters[45][0] = B00000000;
//  letters[45][1] = B00000000;
//  letters[45][2] = B00000000;
//  letters[45][3] = B00011000;
//  letters[45][4] = B00100000;
//  letters[45][5] = B00111000;
//  letters[45][6] = B00001000;
//  letters[45][7] = B00110000;
//  letters[46][0] = B00000000;
//  letters[46][1] = B00000000;
//  letters[46][2] = B00000000;
//  letters[46][3] = B00100000;
//  letters[46][4] = B00100000;
//  letters[46][5] = B00110000;
//  letters[46][6] = B00100000;
//  letters[46][7] = B00011000;
//  letters[47][0] = B00000000;
//  letters[47][1] = B00000000;
//  letters[47][2] = B00000000;
//  letters[47][3] = B00000000;
//  letters[47][4] = B00101000;
//  letters[47][5] = B00101000;
//  letters[47][6] = B00101000;
//  letters[47][7] = B00111000;
//  letters[48][0] = B00000000;
//  letters[48][1] = B00000000;
//  letters[48][2] = B00000000;
//  letters[48][3] = B00000000;
//  letters[48][4] = B00000000;
//  letters[48][5] = B00101000;
//  letters[48][6] = B00101000;
//  letters[48][7] = B00010000;
//  letters[49][0] = B00000000;
//  letters[49][1] = B00000000;
//  letters[49][2] = B00000000;
//  letters[49][3] = B00000000;
//  letters[49][4] = B01000100;
//  letters[49][5] = B01010100;
//  letters[49][6] = B01010100;
//  letters[49][7] = B00101000;
//  letters[50][0] = B00000000;
//  letters[50][1] = B00000000;
//  letters[50][2] = B00000000;
//  letters[50][3] = B00000000;
//  letters[50][4] = B00000000;
//  letters[50][5] = B00101000;
//  letters[50][6] = B00010000;
//  letters[50][7] = B00101000;
//  letters[51][0] = B00000000;
//  letters[51][1] = B00000000;
//  letters[51][2] = B00000000;
//  letters[51][3] = B00101000;
//  letters[51][4] = B00101000;
//  letters[51][5] = B00111000;
//  letters[51][6] = B00001000;
//  letters[51][7] = B00111000;
//  letters[52][0] = B00000000;
//  letters[52][1] = B00000000;
//  letters[52][2] = B00000000;
//  letters[52][3] = B00111000;
//  letters[52][4] = B00001000;
//  letters[52][5] = B00010000;
//  letters[52][6] = B00100000;
//  letters[52][7] = B00111000;
}
