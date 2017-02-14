/*
 * Fais la gestion des envoi et reception des données de vols sur le port
 * relié au Transceiver (RFD900)
 * 
 */


#ifndef _transceiver_h
#define _transceiver_h

#include "Arduino.h"

#include "rocketData.h"
#include "serialPort.h"

#define START_BYTE 's' //Byte de début de buffer d'envoi de données
#define MAX_READ_BYTES 80 //nombre maximal de bytes à lire jusqu'à lire le START_BYTE

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



