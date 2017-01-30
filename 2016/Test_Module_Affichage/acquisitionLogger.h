/*
Fais la gestion de l'enregistrement des donn�es mesur�es par le syst�me d'acquisition
sur une carte SD.
*/

#ifndef _acquisitionLogger_h
#define _acquisitionLogger_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

#include "rocketData.h"

#define FILENAME "data"
#define FILE_EXT ".csv"
#define MAX_NB_OF_FILES 99 //maximum number of files with the same name (except the index)

//CSV header titles
#define TIME_STAMP "Time Stamp"
#define ANG_SPEED_X "Angular Speed X"
#define ANG_SPEED_Y "Angular Speed Y"
#define ANG_SPEED_Z "Angular Speed Z"
#define ACCEL_X "Acceleration X"
#define ACCEL_Y "Acceleration Y"
#define ACCEL_Z "Acceleration Z"
#define MAGNET_X "Magnetic Field X"
#define MAGNET_Y "Magnetic Field Y"
#define MAGNET_Z "Magnetic Field Z"
#define ALTITUDE "Altitude"
#define LATITUDE1 "Latitude 1"
#define LONGITUDE1 "Longitude 1"
#define LATITUDE2 "Latitude 2"
#define LONGITUDE2 "Longitude 2"
#define TEMP_1 "Temperature 1"
#define TEMP_2 "Temperature 2"
//add more temperature title here if needed
#define STRESS_1 "Stress 1"
//add more stress title here if needed

class AcquisitionLogger
{
    public:
    AcquisitionLogger(int csPin, String systemType);
    bool initCard();
    String generateFilename();
    void writeHeader();
    void writeRocketData(RocketPacket packet);

    private:
    int mCsPin;
    String mSystemType;
    File mLoggingFile;
};
#endif
