/*
 * test de la communication avec les RFD900
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

Transceiver RFD_RX;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);

RocketPacket rpktRX;

void setup(){
    Serial.begin(9600);
    Serial.println("La reception va commencer");
    serial_RX.begin();
}

void loop(){
    if (serial_RX.available())
    {
      Serial.println("reception du rocketPacket1");
      rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
      Serial.print("timestamp = ");
      Serial.println(rpktRX.rocketData.timeStamp);
    }
}
