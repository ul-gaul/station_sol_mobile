/*
  Compas.h - Librarie pour le compas utilit� avec la station au sol Arduino 2016.
  Cr�er par Alex Tourigny-Plante et Simon Belley, 24 f�vrier 2016.
  Propri�t� du Groupe a�rospatial de l'Universit� Laval.
*/
#ifndef GPS_h
#define GPS_h

#include "Arduino.h"
#include "TinyGPS.h"
#include "serialPort.h"
#include "rocketData.h"

class GPS
{
  public:
    GPS(SerialPort SerialGPS, int type);
    float getDistance(float lat1, float long1, float lat2, float long2);
    float courseTo(float lat1, float long1, float lat2, float long2);
    unsigned short int getConnection ();
    bool feedGPS(SerialPort SerialGPS);
    void GPSData();
    float getLong();
    float getLat();
    struct InfosGPS
    {
      float mLat;
      float mLong;
      unsigned long mAge;
    };
    void updateCoord(SerialPort SerialGPS);
    RocketPacket getLocation(RocketPacket rocket_packet, SerialPort GPSPort);
    
  private:
    TinyGPS mTinyGPS;
    bool mNewData;
    unsigned short int mSat;
    InfosGPS mInfosGPS;
    float mDistance;
    float mCourse;
    int mType;
};

#endif
