/*
 * test de la librairie de carte sd
 */

#include "transceiver.h"
#include "rocketData.h"
#include "serialPort.h"
#include "acquisitionLogger.h"
// #include "GPS.h"
#include "TinyGPS.h"

#define RFD_PORT_NB 1
#define RFD_BAUD_RATE 57600

// #define LOG_TIME_INTERVAL 1000
// #define SD_CS_PIN 53
// #define SYSTEM_TYPE "r"

#define GPS_PORT_NB 2
#define GPS_BAUD_RATE 9600

typedef struct DataGPS{
    float latitude;
    float longitude;
    unsigned long age;
} DataGPS;

Transceiver RFD_RX;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);

// initializing GPS, type 0 because GPS is mounted on
// ground station
SerialPort serialGPS(GPS_PORT_NB, GPS_BAUD_RATE);
// GPS GPS(&serialGPS, 0);
TinyGPS myTinyGPS;
DataGPS myDataGPS;

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
        // GPS.updateCoord(serialGPS);
        if(feed_gps(serialGPS)){
            myTinyGPS.f_get_position(&myDataGPS.latitude, &myDataGPS.longitude, &myDataGPS.age);
            Serial.print("latitude: ");
            Serial.print(myDataGPS.latitude);
            Serial.print(" longitude: ");
            Serial.print(myDataGPS.longitude);
            Serial.print(" nombre de satellites: ");
            Serial.println(myTinyGPS.satellites());
        }
        // latitude = GPS.getLat();
        // longitude = GPS.getLong();
        // satellites = GPS.getConnection();

    }
}

bool feed_gps(SerialPort serial_port){
    while (serial_port.available() > 0){
        char gps_char = serial_port.read();
        // Serial.print("tinyGPS encode est: ");
        myTinyGPS.encode(serial_port.read());
        // Serial.println(mTinyGPS.encode(SerialGPS.read()));
        // Serial.print("le char lu par serialGPS est: ");
        Serial.println(gps_char);
        if(myTinyGPS.encode(gps_char)){
            Serial.println("feed_gps sucess");
            return true;
        }
    }
    return false;
}
