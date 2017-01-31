#include "Compas.h"

#define MAG_DECLINAISON 0.1745


Compas compass(MAG_DECLINAISON);


void setup(){
    compass.init();
}

void loop(){
    getNorthAngle();
    delay(500);
}
