/*
 
*/


#include "Datadisplay.h"

void DataDisplay::display1(float speed,float acceleration,float maxAlt,float height)
{
  headDisplay();
	speedDisplay(speed);
	accelerationDisplay(acceleration);
	maxAltDisplay(maxAlt);
	altitudeDisplay(height);
	boutonDisplay();
	drawBox();
}
void DataDisplay::headDisplay(){
  GLCD.CursorToXY(6,0);
  GLCD.print("Donnees de vol");
}

void DataDisplay::speedDisplay(float speed)
{
	  GLCD.CursorToXY(5,10);
    GLCD.print("VSI");
    GLCD.CursorToXY(53,10);
    GLCD.print(":");
    GLCD.CursorToXY(62,10);
    GLCD.print(speed);
}

void DataDisplay::accelerationDisplay(float acceleration)
{
	GLCD.CursorToXY(5,20);
    GLCD.print("accel");
    GLCD.CursorToXY(53,20);
    GLCD.print(":");
    GLCD.CursorToXY(62,20);
    GLCD.print(acceleration);
}

void DataDisplay::maxAltDisplay(float maxAlt)
{
	  GLCD.CursorToXY(5,30);
    GLCD.print("max alt.");
    GLCD.CursorToXY(53,30);
    GLCD.print(":");
    GLCD.CursorToXY(62,30);
    GLCD.print(maxAlt);
}

void DataDisplay::altitudeDisplay(float height)
{
	GLCD.CursorToXY(5,40);
    GLCD.print("altitude");
    GLCD.CursorToXY(53,40);
    GLCD.print(":");
    GLCD.CursorToXY(62,40);
    GLCD.print(height);
}

void DataDisplay::boutonDisplay()
{
     GLCD.CursorToXY(6,54);
        GLCD.print("back");
        GLCD.CursorToXY(42,54);
        GLCD.print("<-");
        GLCD.CursorToXY(75,54);
        GLCD.print("->");
        GLCD.CursorToXY(100,54);
        GLCD.print("back");
}

void DataDisplay::display2(float lat1, float long1, float temperature1, float temperature2)
{
  head2Display();
  lat1Display(lat1);
  long1Display(long1);
  temperature1Display(temperature1);
  temperature2Display(temperature2);
  boutonDisplay();
  drawBox();
}

void DataDisplay::head2Display(){
  GLCD.CursorToXY(6,0);
  GLCD.print("Donnees autres");
}


void DataDisplay::lat1Display(float lat1)
{
    GLCD.CursorToXY(5,10);
    GLCD.print("Lat");
    GLCD.CursorToXY(53,10);
    GLCD.print(":");
    GLCD.CursorToXY(62,10);
    GLCD.print(lat1,5);

}

void DataDisplay::long1Display(float long1)
{
  GLCD.CursorToXY(5,20);
    GLCD.print("long");
    GLCD.CursorToXY(53,20);
    GLCD.print(":");
    GLCD.CursorToXY(62,20);
    GLCD.print(long1,5);
}

void DataDisplay::temperature1Display(float temperature1)
{
  GLCD.CursorToXY(5,30);
    GLCD.print("temp. 1");
    GLCD.CursorToXY(53,30);
    GLCD.print(":");
    GLCD.CursorToXY(62,30);
    GLCD.print(temperature1);
}

void DataDisplay::temperature2Display(float temperature2)
{
  GLCD.CursorToXY(5,40);
    GLCD.print("temp. 2");
    GLCD.CursorToXY(53,40);
    GLCD.print(":");
    GLCD.CursorToXY(62,40);
    GLCD.print(temperature2);
}


void DataDisplay::display3(float lat2, float long2, float heading)
{
  head3Display();
  lat2Display(lat2);
  long2Display(long2);
  headingDisplay(heading);
  boutonDisplay();
  drawBox();
}

void DataDisplay::head3Display(){
  GLCD.CursorToXY(6,0);
  GLCD.print("Donnees Station");
}

void DataDisplay::lat2Display(float lat2)
{
    GLCD.CursorToXY(5,13);
    GLCD.print("Lat");
    GLCD.CursorToXY(53,13);
    GLCD.print(":");
    GLCD.CursorToXY(62,13);
    GLCD.print(lat2,5);

}

void DataDisplay::long2Display(float long2)
{
  GLCD.CursorToXY(5,26);
    GLCD.print("long");
    GLCD.CursorToXY(53,26);
    GLCD.print(":");
    GLCD.CursorToXY(62,26);
    GLCD.print(long2,5);
}

void DataDisplay::headingDisplay(float heading)
{
  GLCD.CursorToXY(5,39);
    GLCD.print("heading");
    GLCD.CursorToXY(53,39);
    GLCD.print(":");
    GLCD.CursorToXY(62,39);
    mHeadingDegree = heading/PI*180;
    GLCD.print(mHeadingDegree,2);
}
