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
#endif

#ifdef MULTIPLAYER
SoftwareSerial _serial;
#endif

Gamer *thisGamer = NULL;

ISR(TIMER2_COMPB_vect){
  if(ir == 1){
    thisGamer->isrRoutine();
  }

}


ISR(TIMER2_COMPA_vect){
  if(ir == 0){
    if(player){
     
      if (toggle2){
digitalWrite(2,HIGH);
        toggle2 = 0;
        if(split % 10 == 0 ){
          thisGamer->isrRoutine();
        }
        split++;
      }
      else{
      	digitalWrite(2,LOW);

        toggle2 = 1;
        if(split % 10== 0 ){
          thisGamer->isrRoutine();
        }
        split++;
      } 
      split++;
    }
    else {
    	digitalWrite(2,LOW);
      if(split % 10 == 0 ){
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


void Gamer::play(int notes){
  
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
  OCR2A = notes;
  interrupts();

}

void Gamer::stopPlay(){
 
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

int Gamer::photoDiodeValue() {
  int average[160];
  long total;
  int outcome = 0;
  total = 0;
  for(int i = 0; i < 160; i ++){
    average[i] = analogRead(LDR);

    delayMicroseconds(20);
  }
  for(int j = 0 ; j < 160; j++){
    total = total + average[j];
  }
  outcome = total/160;
  return outcome;
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
void Gamer::updateRow() {
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

// Writes to the TLC5916 LED driver (cathodes)
void Gamer::writeToDriver(byte dataOut) {

  //digitalWrite(OE, HIGH);
    PORTB |= _BV(PORTB2);

  for(int x=0; x<=7; x++) {
  //digitalWrite(CLK1, LOW);
    PORTD &= ~_BV(PORTD6);
     
    digitalWrite(DAT, (dataOut & (1<<x)) >> x);
  // digitalWrite(CLK1, HIGH);
       PORTD |= _BV(PORTD6);
  }

  PORTD &= ~_BV(PORTD6);
    PORTB |= _BV(PORTB1);
   PORTB &= ~_BV(PORTB1);
  //digitalWrite(CLK1, LOW);
  //digitalWrite(LAT, HIGH);
  //digitalWrite(LAT, LOW);
  //digitalWrite(OE, LOW);
   PORTB &= ~_BV(PORTB2);

}



// Write to the MIC5891 shift register (anodes)
void Gamer::writeToRegister(byte dataOut) {
  //digitalWrite(LAT, LOW);

  for(int y=0; y<=7; y++) {
    digitalWrite(DAT, (dataOut & (1<<y)) >> y);
   // digitalWrite(CLK2, HIGH);
   // digitalWrite(CLK2, LOW);
   PORTD |= _BV(PORTD7);
   PORTD &= ~_BV(PORTD7);
  }
    PORTB |= _BV(PORTB1);
   PORTB &= ~_BV(PORTB1);
  //digitalWrite(LAT, HIGH);
  //digitalWrite(LAT, LOW);

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