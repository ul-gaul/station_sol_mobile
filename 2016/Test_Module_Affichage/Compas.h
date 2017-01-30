/*
  Compas.h - Librarie pour le compas utilite avec la station au sol Arduino 2016.
  Creer par Alex Tourigny-Plante et Simon Belley, 24 fevrier 2016.
  Propriete du Groupe aerospatial de l'Universite Laval.
*/
#ifndef Compas_h
#define Compas_h

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_HMC5883_U.h"

class Compas
{
  public:
    Compas(double declinaison);
    float getNorthAngle();
    float getRocketAngle(float x1, float y1, float x2, float y2);
	  bool getEtat();
    void init();
  private:
    float mDeclinaisonAngle;
	Adafruit_HMC5883_Unified mMag;
  float mNorthAngle;
  bool mEtat;
  const float mPi=3.141593;
};

#endif
