
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_HMC5883_U.h"
#include "Compas.h"

// Compas compass(MAG_DECLINAISON)
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
// compass.init();
//mag = Adafruit_HMC5883_Unified(12345);
float northAngle = 0;

void setup(){
    Serial.begin(9600);
    mag.begin();
}

void loop(){
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
    Serial.println(northAngle);
    delay(500);
}
