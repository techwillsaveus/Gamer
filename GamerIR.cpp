#include "GamerIR.h"

/**
	Constructor. Also initiates software serial.
	*/
GamerIR::GamerIR() : _serial(5, 4) {
	_serial.begin(2400);
}
/**
  Sends a string through the IR transmitter.
  @param message the string that will be transmitted
 */
void GamerIR::irSend(String message)
{
  String mes = message;
  for(int i=0; i<mes.length(); i++) {
    _serial.write(mes.charAt(i));
    _serial.write(~mes.charAt(i));
  }
}

/**
  Returns a string received from the IR receiver.
  @return the string received by the IR receiver
 */
String GamerIR::irReceive(){
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

  return message;

}
