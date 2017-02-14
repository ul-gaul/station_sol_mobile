/*
 * This class handle serial port like Default arduino Serial class but
 * with the need to specifie the port number (0,1,2 or 3) only in the constructor
 */

#ifndef _serialPort_h
#define _serialPort_h

#include "Arduino.h"

class SerialPort
{
  public:
  SerialPort();
  SerialPort(int portNumber, long baudrate);
  int available();
  void begin(); //TODO: implement method with config argument
  void end();
  byte read();
  byte readBytes(byte *buffer, int lenght);
  byte readBytesUntil(byte character, byte *buffer, int lenght);
  byte write(byte value); //TODO: implement method with string argument
  byte write(byte *buffer, int lenght); 

  private:
  int mPortNumber;
  long mBaudrate;
};

#endif


