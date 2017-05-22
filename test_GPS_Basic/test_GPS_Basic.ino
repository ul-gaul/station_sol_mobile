/*
 * test de la librairie de carte sd
 */


#include "serialPort.h"
#include "GPS.h"
#include "TinyGPS.h"



#define GPS_PORT_NB 2
#define GPS_BAUD_RATE 9600

typedef struct DataGPS{
    float latitude;
    float longitude;
    unsigned long age;
} DataGPS;

// initializing GPS, type 0 because GPS is mounted on
// ground station
SerialPort serialGPS(GPS_PORT_NB, GPS_BAUD_RATE);
TinyGPS myTinyGPS;
DataGPS myDataGPS;

unsigned short int satellites;
float latitude;
float longitude;

// AcquisitionLogger sdLogger(SD_CS_PIN, SYSTEM_TYPE);

void setup(){
    Serial.begin(9600);
    Serial.println("La reception va commencer");
    serialGPS.begin();
    

}

void loop(){
    if (myTinyGPS.encode(serialGPS.read())) {
        myTinyGPS.f_get_position(&myDataGPS.latitude, &myDataGPS.longitude, &myDataGPS.age);
        Serial.print("latitude: ");
        Serial.print(myDataGPS.latitude);
        Serial.print("longitude: ");
        Serial.print(myDataGPS.longitude);
    
        //latitude = GPS.getLat();
        //longitude = GPS.getLong();
        // satellites = GPS.getConnection();
     //}
    // else{
     // Serial.println("Noooooooooo");
     //}
}
