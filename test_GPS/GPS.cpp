/*
  Compas.cpp - Librarie pour le compas utilite avec la station au sol Arduino 2016.
  Creer par Alex Tourigny-Plante et Simon Belley, 24 fevrier 2016.
  Propriete du Groupe aerospatial de l'Universite Laval.
*/

#include "GPS.h"

// 27-02-2017, modified arguments to pass SerialPort object
// SerialGPS as pointer so begin() method is called on actual
// SerialPort
GPS::GPS(SerialPort* SerialGPS, int type) {
  mType = type;
  SerialGPS->begin();
  TinyGPS mTinyGPS;
}


void GPS::updateCoord(SerialPort SerialGPS)
{
  Serial.println("updatecoords");
  // if(feedGPS(SerialGPS)) {
  //     Serial.println("feedGPS success");
  //     GPSData();
  // }
  // Serial.println("feedGPS fail");
  GPSData();
}

float GPS::getDistance(float lat1, float long1, float lat2, float long2)
{
  mDistance=mTinyGPS.distance_between(lat1, long1, lat2, long2);
  if (mDistance > 100000) {
    return 999;
  }
  return mDistance;
}

float GPS::courseTo(float lat1, float long1, float lat2, float long2)
{
  mCourse=(mTinyGPS.course_to(lat1, long1, lat2, long2))*PI/180;
return mCourse;
}

unsigned short int GPS::getConnection ()
{
  // mSat=mTinyGPS.satellites();
  // if (mSat < 255){
  //   return mSat;
  // } else {
  //   return 0;
  //   }
  return mTinyGPS.satellites();
  }

bool GPS::feedGPS(SerialPort SerialGPS){
    while (SerialGPS.available() > 0){
        char gps_char = SerialGPS.read();
        Serial.print("tinyGPS encode est: ");
        Serial.println(mTinyGPS.encode(SerialGPS.read()));
        Serial.print("le char lu par serialGPS est: ");
        Serial.println(gps_char);
        if(mTinyGPS.encode(gps_char)){
            return true;
        }
    }
    return false;
}

void GPS::GPSData(){
  Serial.println("gpsdata");
  mTinyGPS.f_get_position(&mInfosGPS.mLat, &mInfosGPS.mLong, &mInfosGPS.mAge);
}

float GPS::getLong(){
  return mInfosGPS.mLong;
}

float GPS::getLat(){
  return mInfosGPS.mLat;
}


/*
Returns a RocketPacket at the time the function was called
*/
RocketPacket GPS::getLocation(RocketPacket rocket_packet, SerialPort GPSPort)
{
    updateCoord(GPSPort);
    //Update lat and long
    if(mType == 1){
      rocket_packet.rocketData.latitude1 = mInfosGPS.mLat;
      rocket_packet.rocketData.longitude1 = mInfosGPS.mLong;
    } else if(mType == 2){
      rocket_packet.rocketData.latitude2 = mInfosGPS.mLat;
      rocket_packet.rocketData.longitude2 = mInfosGPS.mLong;
    }

    //return updated rocket_packet
    return rocket_packet;
}
