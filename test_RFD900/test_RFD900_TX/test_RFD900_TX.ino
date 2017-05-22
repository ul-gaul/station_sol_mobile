/*
 * test de la communication avec les RFD900
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

Transceiver RFD_TX;

SerialPort serial_TX(RFD_PORT_NB, RFD_BAUD_RATE);

RocketData rdata1;
RocketData rdata2;

RocketPacket rpkt1;
RocketPacket rpkt2;

void setup(){
    Serial.begin(9600);
    Serial.println("La transmission va commencer");
    // rocket packet 1
    rdata1.timeStamp = 1200;
    rdata1.angSpeedX = 11;
    rdata1.angSpeedY = 12;
    rdata1.angSpeedZ = 13;
    rdata1.accelX = 21;
    rdata1.accelY = 22;
    rdata1.accelZ = 23;
    rdata1.magnetX = 31;
    rdata1.magnetY = 32;
    rdata1.magnetZ = 33;
    rdata1.altitude = 40;
    rdata1.latitude1 = 46.743480;   // coordonnees du
    rdata1.longitude1 = -71.286585; // pont de Quebec
    rdata1.latitude2 = 46.743480;
    rdata1.longitude2 = -71.286585;
    rdata1.temperature1 = 61;
    rdata1.temperature2 = 62;
    rpkt1.rocketData = rdata1;
    // rocket  packet 2
    rdata2.timeStamp = 1200.22;
    rdata2.angSpeedX = 11.22;
    rdata2.angSpeedY = 12.22;
    rdata2.angSpeedZ = 13.22;
    rdata2.accelX = 21.22;
    rdata2.accelY = 22.22;
    rdata2.accelZ = 23.22;
    rdata2.magnetX = 31.22;
    rdata2.magnetY = 32.22;
    rdata2.magnetZ = 33.22;
    rdata2.altitude = 40.22;
    rdata2.latitude1 = 46.743480;   // coordonnees du
    rdata2.longitude1 = -71.286585; // pont de Quebec
    rdata2.latitude2 = 46.743480;
    rdata2.longitude2 = -71.286585;
    rdata2.temperature1 = 61.22;
    rdata2.temperature2 = 62.22;
    rpkt2.rocketData = rdata2;

    serial_TX.begin();
}

void loop(){
    delay(1000);
    Serial.println("envoi du rocketPacket1");
    RFD_TX.sendRocketPacket(rpkt1, serial_TX);
    delay(1000);
    Serial.println("envoi du rocketPacket2");
    RFD_TX.sendRocketPacket(rpkt2, serial_TX);
}
