#include "Gamer.h"
#include "Arduino.h"

int count;
bool toggleVal = false;
int split = 0;
bool ir = false;
bool irTog = false;
bool toneIsPlaying = false;
bool playTog = false;
bool toneStopped = false;
char prevChar;

Gamer *thisGamer = NULL;

// Interrupt service routine.
ISR(TIMER2_COMPB_vect)
{
  if(ir == 1) {
    thisGamer->isrRoutine();
  }

}

// Interrupt service routine for simultaneous IR & buzzer.
ISR(TIMER2_COMPA_vect)
{
  if(ir == 0) {
    if(toneIsPlaying) {
      if (toggleVal) {
        PORTD |= _BV(PORTD2);
        toggleVal = 0;
        if(split % 10 == 0 ){
          thisGamer->isrRoutine();
        }
        split++;
      }
      else {
        PORTD &= ~_BV(PORTD2);
        toggleVal = 1;
        if(split % 10== 0 ) {
          thisGamer->isrRoutine();
        }
        split++;
      }
      split++;
    }
    else {
      PORTD &= ~_BV(PORTD2);
      if(split % 10 == 0 ) {
        thisGamer->isrRoutine();
      }
    }
    split++;
  }
}

/**
  Constructor. Also initiates software serial for IR
	communiation.
 */
//#ifdef MULTIPLAYER
//Gamer::Gamer() : _serial(5,4) {
//}
//#else
Gamer::Gamer() {
}
//#endif
/**
  Plays a tone on the buzzer.
  @param note the desired frequency
 */
void Gamer::playTone(int note)
{
  TIMSK2 &= (1<<OCIE2A);

  if(playTog == false){
    toneStopped = false;
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
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2  = 0;
    TCCR2A |= (1 << WGM21);
    OCR2A = 180;
    TCCR2B |= (1 << CS21);
    TIMSK2 |= (1 << OCIE2A);
    playTog = true;
  }
  toneIsPlaying = true;
  OCR2A = note;
  interrupts();
}

/**
  Stops any frequency on the buzzer pin.
 */
void Gamer::stopTone()
{
  if(toneStopped == false){
    TIMSK2 &= (1<<OCIE1A);
    toneStopped = true;
    toneIsPlaying = false;
    playTog = false;
    OCR2A = 180;
    digitalWrite(2,LOW);
    split = 0;
    toggleVal = 0;
    irTog = false;
    irBegin();
  }

  OCR1A = 14;
  toneIsPlaying = false;
}

/**
  Stops the 38KHz wave for the IR transmitter.
 */
void Gamer::irEnd()
{
  irTog = false;
}

/**
  Creates a 38KHz wave for the IR transmitter.
 */
void Gamer::irBegin()
{
  TIMSK2 &= ~(1<<OCIE2A);
  TIMSK2 &= (1<<OCIE1B);

  if(irTog == false) {

    irTog = true;

    noInterrupts();
    TCCR2A |=  ~(_BV(WGM21));
    TCCR2B |= ~(_BV(CS21));
    TIMSK2 |=  ~(_BV(OCIE2A));
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2  = 0;
    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS22);
    OCR2A = 51;
    OCR2B = 26;
    TCCR2B = (TCCR2B & 0b00111000) | 0x2;
    TIMSK2 = _BV(OCIE2B);
    interrupts();

    ir = 1;
  }
}

/**
  Initialises the library, starts timers, and sets pins. 
 */
void Gamer::begin()
{
  ::thisGamer = this;
	
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

  irBegin();
}

// Inputs --------------------------------

/**
  Checks if a button has been pressed (unique press)
  @param input the button to check
  @return The state of the button
 */
bool Gamer::isPressed(uint8_t input)
{
  if(buttonFlags[input]) {
    buttonFlags[input] = 0;
    return true;
  }
  else return false;
}

/**
  Checks if the button is currently held down.
  @param input the button to check
  @return the state of the button
 */
bool Gamer::isHeld(uint8_t input)
{
  bool result = (PINC & (1<<input)) >> input;
  return !result;
}
/**
  Returns the current value of the LDR
  @return LDR value between 0 and 1023
 */
int Gamer::ldrValue()
{
  return analogRead(LDR);
}
/**
  Changes the "pressed" event threshold for the LDR.
  @param threshold the difference in light that triggers the event
 */
void Gamer::setldrThreshold(uint16_t threshold)
{
  ldrThreshold = threshold;
}

/**
  Gamer v1.9 capacitive touch instead of LDR
*/
bool Gamer::capTouch()
{
	pinMode(19, OUTPUT);

	  digitalWrite(19, LOW);

	  delay(1);

	  // Prevent the timer IRQ from disturbing our measurement

	  noInterrupts();

	  // Make the pin an input with the internal pull-up on

	  pinMode(19, INPUT_PULLUP);



	  // Now see how long the pin to get pulled up. This manual unrolling of the loop

	  // decreases the number of hardware cycles between each read of the pin,

	  // thus increasing sensitivity.

	  uint8_t cycles = 17;

	       if (digitalRead(19)) { cycles =  0;}

	  else if (digitalRead(19)) { cycles =  1;}

	  else if (digitalRead(19)) { cycles =  2;}

	  else if (digitalRead(19)) { cycles =  3;}

	  else if (digitalRead(19)) { cycles =  4;}

	  else if (digitalRead(19)) { cycles =  5;}

	  else if (digitalRead(19)) { cycles =  6;}

	  else if (digitalRead(19)) { cycles =  7;}

	  else if (digitalRead(19)) { cycles =  8;}

	  else if (digitalRead(19)) { cycles =  9;}

	  else if (digitalRead(19)) { cycles = 10;}

	  else if (digitalRead(19)) { cycles = 11;}

	  else if (digitalRead(19)) { cycles = 12;}

	  else if (digitalRead(19)) { cycles = 13;}

	  else if (digitalRead(19)) { cycles = 14;}

	  else if (digitalRead(19)) { cycles = 15;}

	  else if (digitalRead(19)) { cycles = 16;}

	  // End of timing-critical section

	  interrupts();

	  // Discharge the pin again by setting it low and output

	  //  It's important to leave the pins low if you want to 

	  //  be able to touch more than 1 sensor at a time - if

	  //  the sensor is left pulled high, when you touch

	  //  two sensors, your body will transfer the charge between

	  //  sensors.

	  digitalWrite(19, LOW);

	  pinMode(19, OUTPUT);


	  if(cycles > 0){
		  return true;
	  } else {
	  	  return false;
	  }
	
}

// Outputs -------------------------------

/**
  Sets the display's refresh rate. 1 = 1 row per timer cycle. 10 = 1 row every 10 timer cycles.
  @param refreshRate the display's refresh rate modulo against the timer.
 */
void Gamer::setRefreshRate(uint16_t refreshRate)
{
  _refreshRate = refreshRate;
}

/**
  Burns the display[][] array onto the display. Call this when you're done changing pixels in your game.
 */
void Gamer::updateDisplay()
{
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

/**
  Turns on all the pixels on the display.
 */
void Gamer::allOn()
{
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) display[i][j] = 1;
  }
  updateDisplay();
}

/**
  Clears all pixels off the display.
 */
void Gamer::clear()
{
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) display[i][j] = 0;
  }
  updateDisplay();
}

/**
  Prints an 8 byte array onto the display. 
  @param img the 8 byte array to display
 */
void Gamer::printImage(byte* img)
{
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) {
      display[i][j] = (img[j] & (1 << (7-i))) != 0;
    }
  }
  updateDisplay();
}

/**
  Prints an 8 byte array onto the display at an X/Y position.
  @param img the 8 byte array to display
  @param x the image's x position
  @param y the image's y position
 */
void Gamer::printImage(byte* img, int x, int y)
{
  for(int j=0; j<8; j++) {
    for(int i=0; i<8; i++) {
      if(i+x >= 0 && i+x < 8 && j+y >= 0 && j+y < 8) {
        display[i+x][j+y] = (img[j] & (1 << (7-i))) != 0;
      }
    }
  }
  updateDisplay();
}

/**
  Sets the value of the red LED.
  @param value the LED's boolean value
 */
void Gamer::setLED(bool value)
{
  digitalWrite(LED, value);
}

/**
  Toggles the value of the red LED.
 */
void Gamer::toggleLED()
{
  digitalWrite(LED, !digitalRead(LED));
}

/**
  Displays the next row on the display to achieve row scanning.
 */
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

/**
  Writes a byte to the TLC5916 LED driver (cathodes).
  @param dataOut the byte to write to the driver
 */
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

/**
  Writes a byte to the MIC5891 shift register (anodes).
  @param dataOut the byte to write to the register
 */
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

/**
  Checks if inputs have changed to track button and LDR events.
 */
void Gamer::checkInputs()
{
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

/**
  Runs routines within the Interrupt Service Routine.
  Display updating, button event tracking, LDR updating.
 */
void Gamer::isrRoutine()
{
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

/**
  Scrolls a string across the display.
  @param string the string that will be scrolled
 */
void Gamer::printString(String string)
{
  byte screen[8]={0};
  clear();
  for( int index = 0; index<string.length(); index++ ){
    char c = string[index];
    int letIx = 0;
    if( c>='A' && c<='Z' ) letIx = c-'A'+1;
    else if( c>='a' && c<='z' ) letIx = c-'a'+1+26;
    else if( c>='!' && c<='/' ) letIx = c+20;
    else if( c>=':' && c<='@' ) letIx = c+10;
    else if( c>='0' && c<='9' ) letIx = c+27;
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

/**
  Appends the column for scrolling the string across the display.
  @param screen the current screen to append.
  @param col the column to add
 */
void Gamer::appendColumn(byte* screen, byte col)
{
  for( int i=0; i<8; i++){
    screen[i]<<=1;
    if( (col&(1<<(7-i)))!=0 ) screen[i]++;
  }
  printImage(screen);
  delay(70);
}

/**
  Shows the score. Maximum 2 digits :(
  @param n the score to be displayed
 */
void Gamer::showScore(int n)
{
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

/**
  All the letters in the world.
 */
const uint8_t Gamer::allLetters[85][9] = {
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
  {B00100110,B00101010,B00110010,B00000000,LETEND}, // z
  {B11111010,B00000000,LETEND}, // !
  {B11000000,B00000000,B11000000,B00000000,LETEND}, // "
  {B00100100,B01111110,B00100100,B01111110,B00100100,B00000000,LETEND}, // #
  {B01110100,B01010100,B11111110,B01010100,B01011100,B00000000,LETEND}, // $
  {B01100010,B01100100,B00001000,B00010000,B00100110,B01000110,B00000000,LETEND}, // %
  {B00001100,B01010010,B10100010,B01010010,B00001100,B00010010,B00000000,LETEND}, // &
  {B10000000,B01000000,B00000000,LETEND}, // '
  {B01111110,B10000001,B00000000,LETEND}, // (
  {B10000001,B01111110,B00000000,LETEND}, // )
  {B00010000,B01010100,B00111000,B01010100,B00010000,B00000000,LETEND}, // *
  {B00010000,B00010000,B01111100,B00010000,B00010000,B00000000,LETEND}, // +
  {B00000001,B00000010,B00000000,LETEND}, // ,
  {B00010000,B00010000,B00010000,B00010000,B00000000,LETEND}, // -
  {B00000010,B00000000,LETEND}, // .
  {B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B00000000,LETEND}, // /
  {B00100010,B00000000,LETEND}, // :
  {B00000001,B00100010,B00000000,LETEND}, // ;
  {B00010000,B00101000,B01000100,B10000010,B00000000,LETEND}, // <
  {B00100010,B00100010,B00100010,B00000000,LETEND}, // =
  {B10000010,B01000010,B00101000,B00010000,B00000000,LETEND}, // >
  {B01000000,B10000000,B10001101,B10010000,B01100000,B00000000,LETEND}, // ?
  {B01111100,B10000010,B10111010,B10111010,B10001010,B01111010,B00000000,LETEND}, // @
  {B01111100,B10000010,B10000010,B01111100,B00000000,LETEND}, // 0
  {B00100010,B01000010,B11111110,B00000010,B00000010,B00000000,LETEND}, // 1
  {B01000010,B10000110,B10001010,B10010010,B10100010,B01000010,B00000000,LETEND}, // 2
  {B01000100,B10000010,B10010010,B01101100,B00000000,LETEND}, // 3
  {B11110000,B00010000,B00111110,B00000000,LETEND}, // 4
  {B11110010,B10010010,B10010010,B10010010,B10001100,B00000000,LETEND}, // 5
  {B01111100,B10010010,B10010010,B01001100,B00000000,LETEND}, // 6
  {B10000000,B10001110,B10110000,B11000000,B00000000,LETEND}, // 7
  {B01101100,B10010010,B10010010,B01101100,B00000000,LETEND}, // 8
  {B01100000,B10010010,B10010010,B01111100,B00000000,LETEND}, // 9
};

/**
  All the numbers in the world.
 */
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
