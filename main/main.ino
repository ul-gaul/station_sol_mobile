/*
    Programme principal pour l'acquisition de données de la station au sol
    du GAUL - 2017.
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#include "lib/acquisitionLogger.h"
#include "lib/Compas.h"
#include "lib/rocketData.h"
#include "lib/serialPort.h"
#include "lib/TinyGPS.h"
#include "lib/transceiver.h"
#include "Arduino.h"

#define RFD_PORT 1
#define GPS_PORT 2
// pin SDA 20
// pin SCL 21 pour le Compas
#define LCD_D0 22
#define LCD_D1 23
#define LCD_D2 24
#define LCD_D3 25
#define LCD_D4 26
#define LCD_D5 27
#define LCD_D6 28
#define LCD_D7 29
#define LCD_CS1 34
#define LCD_CS2 33
#define LCD_RW 35
#define LCD_RS 36
#define LCD_E 37
#define BTN_1 49
#define BTN_2 47
#define BTN_3 45
#define BTN_4 43
// carte SD: MISO 50
// MOSI 51, SCK 52, CS 53
#define SD_CHIP_SELECT 53

#define RFD_BAUDRATE 57600
#define GPS_BAUDRATE 9600

#define MAG_DECLINAISON 0
#define LOG_TIME_INTERVAL 1000
#define SYSTEM_TYPE "r"

float northAngle = 0;
float latitude = 0;
float longitude = 0;

Transciever RFD_RX;
RocketPacket rpktRX;
TinyGPS gps;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUD_RATE);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
AcquisitionLogger sdLogger(SD_PIN, SYSTEM_TYPE);

typedef enum menus {MAIN, WATCH_ROCKET, FIND_ROCKET} menus;

void Log_Start(){
  while(!test_init_sd){
    test_init_sd = sdLogger.initCard();
  }
  sdLogger.writeHeader();
}

void Log_Rocket_Data(){
  if (serial_RX.available()){
    rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
    sdLogger.writeRocketData(rpktRX);
  }
}

void Get_North_Angle(){
  sensors_event_t event;
  mag.getEvent(&event);
  northAngle = atan2(event.magnetic.y, event.magnetic.x);
  northAngle += MAG_DECLINAISON;
  if(northAngle < 0){
      northAngle += 2*PI;
  }
  else if(northAngle > 2*PI){
      northAngle -= 2*PI;
  }
}

void Get_Position (){
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      if (gps.encode(c))
        newData = true;
    }
  }
  if (newData)
  {
    unsigned long age;
    gps.f_get_position(&latitude, &longitude, &age);
  }
}

void setup(){
  serial_RX.begin();
  mag.begin();
  Serial2.begin();
  Log_Start();
}

void loop(){
  Log_Rocket_Data();  //Receives Data from the rocket and logs it into the SD card
  Get_North_Angle();  //Gets the orientation of the base station
  Get_Position();     //Gets the position of the base station

}
