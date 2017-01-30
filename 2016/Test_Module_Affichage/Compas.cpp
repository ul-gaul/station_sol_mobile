/*
  Compas.cpp - Librarie pour le compas utilite avec la station au sol Arduino 2016.
  Creer par Alex Tourigny-Plante et Simon Belley, 24 fevrier 2016.
  Propriete du Groupe aerospatial de l'Universite Laval.
*/

#include "Compas.h"



Compas::Compas(double declinaison){
	mMag = Adafruit_HMC5883_Unified(12345);
	mDeclinaisonAngle = declinaison;
  
}

void Compas::init(){
  mEtat = mMag.begin();
}

bool Compas:: getEtat(){
  return mEtat;
}
	


float Compas::getNorthAngle(){
  //Retourne l'angle du nord en radian. (0 rad = nord, pi/2 rad = est)
  sensors_event_t event;
  mMag.getEvent(&event);
  mNorthAngle=atan2(event.magnetic.y, event.magnetic.x);
  mNorthAngle+=mDeclinaisonAngle;
  if(mNorthAngle < 0)
  {
    mNorthAngle+=(2*PI);
  }
  if(mNorthAngle > (2*PI))
  {
    mNorthAngle-=(2*PI);
  }
  return mNorthAngle;
}

 float Compas::getRocketAngle(float x1, float y1, float x2, float y2)
{
  //Donne l'angle à partir du nord pour rejoindre la cible
float RocketAngle=atan2(abs(y1-y2),abs(x1-x2));
if(y2 > y1)
  {
    RocketAngle=(PI/2)-RocketAngle;
  }
else
  {
    RocketAngle=(PI/2)+RocketAngle;
  }
if(x2 > x1)
  {
    RocketAngle=mNorthAngle+RocketAngle;
  }
else
  {
    RocketAngle=mNorthAngle-RocketAngle;
  }
  return RocketAngle;
}

