/*
 * test de la librairie de carte sd
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"
#include "acquisitionLogger.h"
#include "GPS.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

// #define LOG_TIME_INTERVAL 1000
// #define SD_CS_PIN 53
// #define SYSTEM_TYPE "r"

#define GPS_PORT_NB 2
#define GPS_BAUD_RATE 9600

Transceiver RFD_RX;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);

// initializing GPS, type 0 because GPS is mounted on
// ground station
SerialPort serialGPS(GPS_PORT_NB, GPS_BAUD_RATE);
GPS GPS(&serialGPS, 0);

unsigned short int satellites;
float latitude;
float longitude;

RocketPacket rpktRX;

// AcquisitionLogger sdLogger(SD_CS_PIN, SYSTEM_TYPE);

void setup(){
    Serial.begin(9600);
    Serial.println("La reception va commencer");
    serial_RX.begin();
    serialGPS.begin();
    // initialization of sd card
    // try over and over until it works
    // bool test_init_sd = false;
    // while(!test_init_sd){
    //     test_init_sd = sdLogger.initCard();
    //     if(!test_init_sd){
    //         Serial.println("failed");
    //     } else {
    //         Serial.println("sucess");
    //     }
    // }
    // sdLogger.writeHeader();

}

void loop(){
    if (serial_RX.available()){
        // receive rocketPacket from RFD
        rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
        // write the data from the packet to the SD card
        // sdLogger.writeRocketData(rpktRX);
        GPS.updateCoord(serialGPS);
        latitude = GPS.getLat();
        longitude = GPS.getLong();
        satellites = GPS.getConnection();
        Serial.print("latitude: ");
        Serial.print(latitude);
        Serial.print(" longitude: ");
        Serial.print(longitude);
        Serial.print(" nombre de satellites: ");
        Serial.println(satellites);
    }
}