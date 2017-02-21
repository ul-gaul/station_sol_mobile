#include "serialPort.h"

SerialPort::SerialPort()
{
  mPortNumber = 0;
  mBaudrate = 9600;
}

SerialPort::SerialPort(int portNumber, long baudrate)
{
    mPortNumber = portNumber;
    mBaudrate = baudrate;
} 

int SerialPort::available()
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.available();
        case 1:
            return Serial1.available();
        case 2:
            return Serial2.available();
        case 3:
            return Serial3.available();
        default:
            return 0;
    }
}

void SerialPort::begin()
{
    switch (mPortNumber)
    {
        case 0:
            Serial.begin(mBaudrate);
        case 1:
            Serial1.begin(mBaudrate);
        case 2:
            Serial2.begin(mBaudrate);
        case 3:
            Serial3.begin(mBaudrate);
    }
}

void SerialPort::end()
{
    switch (mPortNumber)
    {
        case 0:
            Serial.end();
        case 1:
            Serial1.end();
        case 2:
            Serial2.end();
        case 3:
            Serial3.end();
    }
}

byte SerialPort::read()
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.read();
        case 1:
            return Serial1.read();
        case 2:
            return Serial2.read();
        case 3:
            return Serial3.read();
        default:
            return 0;
    }
}

byte SerialPort::readBytes(byte *buffer, int lenght)
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.readBytes(buffer, lenght);
        case 1:
            return Serial1.readBytes(buffer, lenght);
        case 2:
            return Serial2.readBytes(buffer, lenght);
        case 3:
            return Serial3.readBytes(buffer, lenght);
        default:
            return 0;
    }
}

byte SerialPort::readBytesUntil(byte character, byte *buffer, int lenght)
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.readBytesUntil(character, buffer, lenght);
        case 1:
            return Serial1.readBytesUntil(character, buffer, lenght);
        case 2:
            return Serial2.readBytesUntil(character, buffer, lenght);
        case 3:
            return Serial3.readBytesUntil(character, buffer, lenght);
        default:
            return 0;
    }
}

byte SerialPort::write(byte value)
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.write(value);
        case 1:
            return Serial1.write(value);
        case 2:
            return Serial2.write(value);
        case 3:
            return Serial3.write(value);
        default:
            return 0;
    }
}

byte SerialPort::write(byte *buffer, int lenght)
{
    switch (mPortNumber)
    {
        case 0:
            return Serial.write(buffer, lenght);
        case 1:
            return Serial1.write(buffer, lenght);
        case 2:
            return Serial2.write(buffer, lenght);
        case 3:
            return Serial3.write(buffer, lenght);
        default:
            return 0;
    }
}
