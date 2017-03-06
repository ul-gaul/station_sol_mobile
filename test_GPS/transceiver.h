/*
 * Fais la gestion des envoi et reception des donnÃ©es de vols sur le port
 * reliÃ© au Transceiver (RFD900)
 * 
 */


#ifndef _transceiver_h
#define _transceiver_h

#include "Arduino.h"

#include "rocketData.h"
#include "serialPort.h"

#define START_BYTE 's' //Byte de dÃ©but de buffer d'envoi de donnÃ©es
#define MAX_READ_BYTES 80 //nombre maximal de bytes Ã  lire jusqu'Ã  lire le START_BYTE

class Transceiver
{
  public:
  Transceiver();
  
  //Pour le calcul de checksum
  byte calculateChecksum(byte *data);
  
  //Gestion de la communication serial
  void initCommunication();
  void sendRocketPacket(RocketPacket packet, SerialPort serialPort);
  RocketPacket receiveRocketPacket(RocketPacket packet, SerialPort serialPort);
};

#endif




