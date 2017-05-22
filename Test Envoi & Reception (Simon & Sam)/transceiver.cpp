#include "transceiver.h"

Transceiver::Transceiver()
{}

byte Transceiver::calculateChecksum(byte *data)
{
  byte sum = 0;
  for (int i=0;i<sizeof(RocketData);i++)
  {
    sum += data[i];
  }
  return sum; //temporaire
}

void Transceiver::sendRocketPacket(RocketPacket packet, SerialPort serialPort)
{
  byte dataBuffer[sizeof(RocketData)];
  byte packetBuffer[sizeof(RocketPacket)];
  
  //Calculate checksum on input rocket data
  memcpy(dataBuffer, &(packet.rocketData), sizeof(RocketData));
  packet.checksum = calculateChecksum(dataBuffer);
  memcpy(packetBuffer, &packet, sizeof(RocketPacket)); 

  //Send Data to serialPort port
  serialPort.write(START_BYTE);
  serialPort.write(packetBuffer, sizeof(RocketPacket));
}

RocketPacket Transceiver::receiveRocketPacket(RocketPacket packet, SerialPort serialPort)
{
  RocketPacket tmpPacket; //Temporary Rocket Packet used for checksum validation return
  byte dataBuffer[sizeof(RocketData)];
  byte packetBuffer[sizeof(RocketPacket)];
  byte dummyBuffer[MAX_READ_BYTES];

  //Read serial port
  if (serialPort.available())
  {
    //Read port until START_BYTE
    char check = serialPort.read();
    if (check != START_BYTE)
    {
      byte nbOfBytes = serialPort.readBytesUntil(START_BYTE, dummyBuffer, MAX_READ_BYTES);
//      if (nbOfBytes >= MAX_READ_BYTES) //if unable to read start character
//      {
//        return packet;
//      }
    }

    //Read Data and Calculate Checksum
    serialPort.readBytes(packetBuffer, sizeof(RocketPacket));
    memcpy(&tmpPacket, packetBuffer, sizeof(RocketPacket));
    memcpy(dataBuffer, &tmpPacket.rocketData, sizeof(RocketData));
    byte checksum = calculateChecksum(dataBuffer);
    if (checksum == tmpPacket.checksum)
    {
      return tmpPacket;
    }
    else
    {
      return packet; 
    }
  }
}
