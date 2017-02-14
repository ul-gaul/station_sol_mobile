#ifndef _rocketData_h
#define _rocketData_h

typedef struct
{
    //Time Stamp
    float timeStamp;

    //Angular Speed in Radian per Second
	float angSpeedX;
	float angSpeedY;
	float angSpeedZ;

	//Acceleration in g
	float accelX;
	float accelY;
	float accelZ;

	//Magnetic Fields in Gauss
	float magnetX;
	float magnetY;
	float magnetZ;

	//Altitude in meter
	float altitude;

	//GPS Coordinates in degrees
	float latitude1;
	float longitude1;
	float latitude2;
	float longitude2;

    //Temperature in Celsius degrees
    float temperature1;
    float temperature2;
    //add more temperature entries here if needed

} RocketData;

typedef struct
{
    RocketData rocketData;
	byte checksum;
} RocketPacket;

#endif
