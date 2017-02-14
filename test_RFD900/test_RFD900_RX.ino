/*
 * test de la communication avec les RFD900
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

Transceiver RFD_RX();

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);

// RocketData rdata1;
// rdata1.timeStamp = 1200;
// rdata1.angSpeedX = 11;
// rdata1.angSpeedY = 12;
// rdata1.angSpeedZ = 13;
// rdata1.accelX = 21;
// rdata1.accelY = 22;
// rdata1.accelZ = 23;
// rdata1.magnetX = 31;
// rdata1.magnetY = 32;
// rdata1.magnetZ = 33;
// rdata1.altitude = 40;
// rdata1.latitude1 = 51;
// rdata1.longitude1 = 52;
// rdata1.latitude2 = 53;
// rdata1.longitude2 = 54;
// rdata1.temperature1 = 61;
// rdata1.temperature2 = 62;
//
// RocketPacket rpkt1;
// rpkt1.rocketData = rdata1;
// rpkt1.checksum = TX.calculateChecksum(&rdata1);

RocketPacket rpktRX;

void setup(){
    Serial.println("La reception va commencer");
    serial_RX.begin();
}

void loop(){
    Serial.println("reception du rocketPacket1");
    RFD_RX.sendRocketPacket(rpkt1);
    rpktRX = RFD_RX.receiveRocketPacket(rpktRX, RFD_PORT_NB);
    Serial.print("timestamp = ");
    Serial.println(rpktRX.rocketData.timeStamp);
}
