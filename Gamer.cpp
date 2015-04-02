#define sbi(port,bit) (port)|=(1<<(bit))

int count;
bool toggle2 = false;
int split = 0;

bool ir = false;
bool irTog = false;

bool player = false;
bool playTog = false;
bool playStop = false;

char prevChar;

#include "Gamer.h"
#include "Arduino.h"

// Include SoftSerial for IR communication
#ifdef MULTIPLAYER
#include "SoftwareSerial.h"
SoftwareSerial _serial;
#endif


Gamer *thisGamer = NULL;

ISR(TIMER2_COMPB_vect)
{
  if(ir == 1) {
    thisGamer->isrRoutine();
  }

}

ISR(TIMER2_COMPA_vect)
{
  if(ir == 0) {
    if(player) {
      if (toggle2) {
        // digitalWrite(2,HIGH);
        PORTD |= _BV(PORTD2);
        toggle2 = 0;
        if(split % 10 == 0 ){
          thisGamer->isrRoutine();
        }
        split++;
      }
      else {
      	// digitalWrite(2,LOW);
        PORTD &= ~_BV(PORTD2);
        toggle2 = 1;
        if(split % 10== 0 ) {
          thisGamer->isrRoutine();
        }
        split++;
      } 
      split++;
    }
    else {
    	// digitalWrite(2,LOW);
      PORTD &= ~_BV(PORTD2);
      if(split % 10 == 0 ) {
        thisGamer->isrRoutine();
      }
    }
    split++;
  }
}

#ifdef MULTIPLAYER
Gamer::Gamer() : _serial(5,4){
}
#endif
#ifndef MULTIPLAYER
Gamer::Gamer(){
}
#endif


void Gamer::playTone(int note){

  TIMSK2 &= (1<<OCIE2A);

  if(playTog == false){
    playStop = false;
    irTog = true;
    ir = 0;
    noInterrupts();

    TCCR2A = ~(_BV(COM2B1)) | ~(_BV(WGM21)) | ~(_BV(WGM20));
    TCCR2B = ~(_BV(WGM22)) | ~(_BV(CS22));
    TCCR2B = (TCCR2B & 0b0000000) | 0;
    TIMSK2 = ~(_BV(OCIE2B));


    OCR2A = 0;
    TIMSK2 = 0;
    OCR2B = 0;
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    TCCR2A |= (1 << WGM21);
    OCR2A = 180;
    TCCR2B |= (1 << CS21);   
    TIMSK2 |= (1 << OCIE2A);
    playTog = true;
  }
  player = true;
  OCR2A = note;
  interrupts();

}

void Gamer::stopTone(){

  if(playStop == false){
    TIMSK2 &= (1<<OCIE1A);
    playStop = true;
    player = false;
    playTog = false;
    OCR2A = 180;
    digitalWrite(2,LOW);
    split = 0; 
    toggle2 = 0;
    irTog = false;
    irPlay();
  }

  OCR1A = 14;
  player = false;
}

void Gamer::irStop(){

  irTog = false;
}
void Gamer::irPlay(){

 TIMSK2 &= ~(1<<OCIE2A);
 TIMSK2 &= (1<<OCIE1B);
 if(irTog == false){

  irTog = true;
  
  noInterrupts();
  TCCR2A |=  ~(_BV(WGM21));
  TCCR2B |= ~(_BV(CS21));   
  TIMSK2 |=  ~(_BV(OCIE2A));
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2  = 0;//initialize counter value to 0
    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS22);
    OCR2A = 51;
    OCR2B = 26;
    TCCR2B = (TCCR2B & 0b00111000) | 0x2;
    TIMSK2 = _BV(OCIE2B);
    interrupts();

    ir = 1;
     //stopPlay();
  }

}

// Setup inputs, outputs, timers, etc. Call this from setup()!!
void Gamer::begin() {

  ::thisGamer = this;

  #ifdef MULTIPLAYER
  _serial.begin(2400);
  #endif

  _refreshRate = 50;
  ldrThreshold = 300;

  // Setup outputs
  pinMode(3, OUTPUT);
  for(int i=6; i<=10; i++) pinMode(i, OUTPUT);
    pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(5,INPUT);




  // Setup inputs
  DDRC = B00000;
  PORTC = B11111;

  //Analog Read 16 divisor
  ADCSRA &= ~(1 << ADPS2);

  irPlay();   

  

}

// Inputs --------------------------------

// Returns true if a button has been pressed recently
bool Gamer::isPressed(uint8_t input) {
  if(buttonFlags[input]) {
    buttonFlags[input] = 0;
    return true;
  }
  else return false;
}

// Returns true if the button is currently held down
bool Gamer::isHeld(uint8_t input) {
  bool result = (PINC & (1<<input)) >> input;
  return !result;
}

// Returns the current value of the LDR
int Gamer::ldrValue() {
  return analogRead(LDR);
}

// Change the button threshold for the LDR.
void Gamer::setldrThreshold(uint16_t threshold) {
  ldrThreshold = threshold;
}

// Outputs -------------------------------

// Set the display's refresh rate. 1 = 1 row per timer cycle. 10 = 1 row every 10 timer cycles
void Gamer::setRefreshRate(uint16_t refreshRate) {
  _refreshRate = refreshRate;
}

// Burns the display[][] array onto the display. Only call when you're done changing pixels!
void Gamer::updateDisplay() {
  byte newImage[8];
  for(int j=0; j<8; j++) {
    newImage[j] = 0x00;
    for(int i=0; i<8; i++) {
      newImage[j] <<= 1;
      newImage[j] |= display[i][j];
    }
  }
  if(newImage != image) {
    for(int i=0; i<8; i++) image[i] = newImage[i];
  }
}

// Turn on all pixels on display
void Gamer::allOn() {
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) display[i][j] = 1;
  }
updateDisplay();
}

void Gamer::clear() {
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) display[i][j] = 0;
  }
updateDisplay();
}

// Print an 8 byte array onto the display
void Gamer::printImage(byte* img) {
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) {
      display[i][j] = (img[j] & (1 << (7-i))) != 0;
    }
  }
  updateDisplay();
}

// Set the value of the Gamer LED
void Gamer::setLED(bool value) {
  digitalWrite(LED, value);
}

// Toggle the Gamer LED
void Gamer::toggleLED() {
  digitalWrite(LED, !digitalRead(LED));
}

// Internal display refreshing and writing to ICs ----------------------

// Load the next row in the display.
void Gamer::updateRow() 
{
  if(counter==8) {
    counter = 0;
    currentRow = 0x80;
  }
  writeToRegister(0);
  writeToDriver(image[counter]);
  writeToRegister(currentRow);
  currentRow >>= 1;
  counter++;
}

void Gamer::startAnimation()
{
  
}

// Writes to the TLC5916 LED driver (cathodes)
void Gamer::writeToDriver(byte dataOut) 
{
  // Output enable HIGH
  PORTB |= _BV(PORTB2);

  // Send byte to driver
  for(int x=0; x<=7; x++) {
    PORTD &= ~_BV(PORTD6);
    if(((dataOut & (1<<x)) >> x)) PORTB |= _BV(PORTB0);
    else PORTB &= ~_BV(PORTB0);
    PORTD |= _BV(PORTD6);
  }

  PORTD &= ~_BV(PORTD6);
  PORTB |= _BV(PORTB1);
  PORTB &= ~_BV(PORTB1);
  PORTB &= ~_BV(PORTB2);
}

// Write to the MIC5891 shift register (anodes)
void Gamer::writeToRegister(byte dataOut) 
{
  for(int y=0; y<=7; y++) {
    if((dataOut & (1<<y)) >> y) PORTB |= _BV(PORTB0);
    else PORTB &= ~_BV(PORTB0);
    PORTD |= _BV(PORTD7);
    PORTD &= ~_BV(PORTD7);
  }
  PORTB |= _BV(PORTB1);
  PORTB &= ~_BV(PORTB1);
}

// Periodically check if inputs are pressed (+ debouncing)
void Gamer::checkInputs() {

  for(int i=0; i<6; i++) {
    if(i != 5) {
      currentInputState[i] = (PINC & (1<<i)) >> i;
      if(currentInputState[i] != lastInputState[i]) {
        if(currentInputState[i] == 0) {
          buttonFlags[i] = 1;
        }
      }
      lastInputState[i] = currentInputState[i];
    }
    else {
      currentInputState[i] = analogRead(LDR);
      if(currentInputState[i] - lastInputState[i] >= ldrThreshold) buttonFlags[i] = 1;
      lastInputState[i] = currentInputState[i];
    }

  }
}

// Run Interrupt Service Routine tasks
void Gamer::isrRoutine() {

  if(ir == 1){
    pulseCount++;
    if(pulseCount >= _refreshRate) {
      updateRow();
      pulseCount = 0;
    }
    if(pulseCount == _refreshRate/2) {
      checkInputs();
    }
  }


  if (ir == 0){
    updateRow();
    checkInputs();
  }

}

#ifdef MULTIPLAYER
void Gamer::sendIr(String message){
//irPlay();
  String mes = message;
//mes = '$'+ mes + '*';
  for(int i=0; i<mes.length(); i++) {
    _serial.write(mes.charAt(i));
    _serial.write(~mes.charAt(i));
  }

}

String Gamer::irReceive(){
//irPlay();
  char ch;
  String message;
  char cch,incch;

  int n, i;
  n = _serial.available();
  
  
  i = n;

  while(i--){
    ch = _serial.read();
    if(ch == ~prevChar) message = message+prevChar;
    prevChar = ch;

  }

  String messo = message;
  return message;

}
#endif

void Gamer::printString(String string) {
  byte screen[8]={0};
  clear();
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

void Gamer::appendColumn(byte* screen, byte col){
  for( int i=0; i<8; i++){
    screen[i]<<=1;
    if( (col&(1<<(7-i)))!=0 ) screen[i]++;
  }
  printImage(screen);
  delay(70);
}

void Gamer::showScore(int n) {
  byte result[8];
  int dig1=n/10;
  int dig2=n%10;
  for(int p=0;p<8;p++) {
    result[p]=allNumbers[dig2][p];
    if( dig1>0 ) 
      result[p]|=(allNumbers[dig1][p]<<4);
  }
  printImage(result);
}

const uint8_t Gamer::allLetters[53][9] = {
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

const uint8_t Gamer::allNumbers[10][8] = {
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
