/*
 * test de la librairie de carte sd
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"
#include "acquisitionLogger.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

#define LOG_TIME_INTERVAL 1000
#define SD_CS_PIN 53
#define SYSTEM_TYPE "r"

Transceiver RFD_RX;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);

RocketPacket rpktRX;

AcquisitionLogger sdLogger(SD_CS_PIN, SYSTEM_TYPE);

void setup(){
    Serial.begin(9600);
    Serial.println("La reception va commencer");
    serial_RX.begin();
    // initialization of sd card
    // try over and over until it works
    bool test_init_sd = false;
    while(!test_init_sd){
        test_init_sd = sdLogger.initCard();
    }
    sdLogger.writeHeader();
}

void loop(){
    if (serial_RX.available())
    {
        Serial.println("reception du rocketPacket1");
        // receive rocketPacket from RFD
        rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
        // write the data from the packet to the SD card
        sdLogger.writeRocketData(rpktRX);
        Serial.print("timestamp = ");
        Serial.println(rpktRX.rocketData.timeStamp);
    }
}
