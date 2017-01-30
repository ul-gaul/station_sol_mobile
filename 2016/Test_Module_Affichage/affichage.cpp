#include "affichage.h"

affichage::affichage()
{
  TrackingDisplay trackingDisplay;
}

void affichage::displayAccueil(){
  GLCD.ClearScreen();
  accueilDisplay.display1();
}

void affichage::displayConnection(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat)
{
  GLCD.ClearScreen();
  connectionDisplay.display1(SDEtat, CompasEtat, RFDEtat, sat);
}

void affichage::displayData(float speed,float acceleration,float temperature,float height)
{
  GLCD.ClearScreen();
  dataDisplay.display1(speed, acceleration, temperature, height);
}

void affichage::displayData2(float lat1, float long1, float temperature1, float temperature2)
{
  GLCD.ClearScreen();
  dataDisplay.display2(lat1, long1, temperature1, temperature2);
}

void affichage::displayData3(float lat2, float long2, float heading)
{
  GLCD.ClearScreen();
  dataDisplay.display3(lat2, long2, heading);
}

void affichage::displayTracking(float trackAngle,float northAngle,float distance)
{
  GLCD.ClearScreen();
  trackingDisplay.display1(trackAngle, northAngle, distance);
}

bool affichage::displayTracking2(int pos,int action)
{
  GLCD.ClearScreen();
  trackingDisplay.display2(pos);
  if (action==10)
  {
    trackingDisplay.incrementer(pos);
  }
  if (action==11){
    trackingDisplay.decrementer(pos);
  }
  if (pos==11) {
    mCoord=trackingDisplay.coordManuel();
  }
  return mCoord;
}

float affichage::getManuelLat()
{
  return trackingDisplay.getLat();
}


float affichage::getManuelLong()
{
  return trackingDisplay.getLong();
}

bool affichage::getManuelCoord()
{
  return trackingDisplay.coordManuel();
}

