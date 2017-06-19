#include "acquisitionLogger.h"

AcquisitionLogger::AcquisitionLogger(int csPin, String systemType)
{
    /*
    Contructor
    param csPin : SPI chip select pin
    param systemType : represents type of electronic system, can be "a" for acquisition or "r" for reception.
    */
    mCsPin = csPin;
    mSystemType = systemType;
}

bool AcquisitionLogger::initCard()
{
    /*
    Initialise SD card and create file and directory
    return: True if initialization succeeds, false if fails
    */
    bool succes;

    //init Card
    succes = SD.begin(mCsPin);
    if (succes)
    {
        //Create File
        if (!SD.exists(mSystemType))
        {
          Serial.println("directory doesn't not exist, creating new one");
          SD.mkdir(mSystemType);
        }
        String filename = generateFilename();
        mLoggingFile = SD.open(filename, FILE_WRITE);
        if (!mLoggingFile)
        {
          Serial.println("File creation failed");
          return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

String AcquisitionLogger::generateFilename()
{
    /*
    Generate unique filename with index
    return : Logging filename
    */
    String filename;
    //Verify file names that already exist to create unique filename.
    //If max nb of files is reached, last filename will be returned and the next
    //data to be saved will be appended to file. Because of this, it's important
    //to regularly clear files from SD card.
    for (int i = 1; i <= MAX_NB_OF_FILES; i++)
    {
        filename = mSystemType + "/" + FILENAME + String(i) + FILE_EXT;
        if (!SD.exists(filename))
        {
            break;
        }
    }
    return filename;
}

void AcquisitionLogger::writeHeader()
{
    /*
    Write csv header using RocketData format (This fonction needs to be modified if RocketData changes)
    */
    mLoggingFile.print(TIME_STAMP); mLoggingFile.print(",");
    mLoggingFile.print(ANG_SPEED_X); mLoggingFile.print(",");
    mLoggingFile.print(ANG_SPEED_Y); mLoggingFile.print(",");
    mLoggingFile.print(ANG_SPEED_Z); mLoggingFile.print(",");
    mLoggingFile.print(ACCEL_X); mLoggingFile.print(",");
    mLoggingFile.print(ACCEL_Y); mLoggingFile.print(",");
    mLoggingFile.print(ACCEL_Z); mLoggingFile.print(",");
    mLoggingFile.print(ALTITUDE); mLoggingFile.print(",");
    mLoggingFile.print(LATITUDE1); mLoggingFile.print(",");
    mLoggingFile.print(LONGITUDE1); mLoggingFile.print(",");
    mLoggingFile.print(LATITUDE2); mLoggingFile.print(",");
    mLoggingFile.print(LONGITUDE2); mLoggingFile.print(",");
    mLoggingFile.print(TEMP_1); mLoggingFile.print(",");
    mLoggingFile.print(TEMP_2); mLoggingFile.print(",");
    mLoggingFile.print(TEMP_3); mLoggingFile.print(",");
    mLoggingFile.print(TIME_STAMP_DATE); mLoggingFile.print(",");
    mLoggingFile.print(QUATERNIONA); mLoggingFile.print(",");
    mLoggingFile.print(QUATERNIONB); mLoggingFile.print(",");
    mLoggingFile.print(QUATERNIONC); mLoggingFile.print(",");
    mLoggingFile.print(QUATERNIOND); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_ACQUISITION1); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_ACQUISITION2); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_ACQUISITION3); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_ALIM1); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_ALIM2); mLoggingFile.print(",");
    mLoggingFile.print(ETAT_BOARD_PAYLOAD1); mLoggingFile.print(",");
    mLoggingFile.print(ALIM_VOLTAGE); mLoggingFile.print(",");
    mLoggingFile.print(ALIM_COURANT); mLoggingFile.print(",");
    mLoggingFile.print(PAYLOAD_ANG_SPEEDX); mLoggingFile.print(",");
    mLoggingFile.print(PAYLOAD_ANG_SPEEDY); mLoggingFile.print(",");
    mLoggingFile.print(PAYLOAD_ANG_SPEEDZ); mLoggingFile.print(",");
    mLoggingFile.print(CAMERA); mLoggingFile.print(",");
    mLoggingFile.print(DEPLOIEMENT); mLoggingFile.print(",");
    mLoggingFile.println();
    mLoggingFile.flush();
}

void AcquisitionLogger::writeRocketData(RocketPacket packet)
{
    /*
    Write Rocket Data in csv file
    param packet : RocketPacket including valid RocketData
    */
    mLoggingFile.print(packet.rocketData.timeStamp); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedX); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedY); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedZ); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.accelX); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.accelY); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.accelZ); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.altitude); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.latitude1, 7); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.longitude1, 7); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.latitude2, 7); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.longitude2, 7); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.temperature1); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.temperature2); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.temperature3); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.timeStampDate); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.quaterniona); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.quaternionb); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.quaternionc); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.quaterniond); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardAcquisition1); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardAcquisition2); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardAcquisition3); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardAlim1); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardAlim2); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.etatBoardPayload1); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.voltage); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.courant); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedXPayload); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedYPayload); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.angSpeedZPayload); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.camera); mLoggingFile.print(",");
    mLoggingFile.print(packet.rocketData.deploiement); mLoggingFile.print(",");
    mLoggingFile.println();
    mLoggingFile.flush();
}
