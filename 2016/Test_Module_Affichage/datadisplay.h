/*
Fais la gestion de l'enregistrement des donn�es mesur�es par le syst�me d'acquisition
sur une carte SD.
*/

#ifndef _DataDisplay_h
#define _DataDisplay_h_h
#include "Menu.h"
class DataDisplay: public Menu
{	public:
	void boutonDisplay();
 
	void display1(float speed,float acceleration,float temperature,float height);
	void speedDisplay(float speed);
	void accelerationDisplay(float acceleration);
  void maxAltDisplay(float maxAlt);
	void altitudeDisplay(float height);
  void headDisplay();

  
  void display2(float lat1, float long1, float temperature1, float temperature2);
  void lat1Display(float lat1);
  void long1Display(float long1);
  void temperature1Display(float temperature1);
  void temperature2Display(float temperature2);
  void head2Display();

  void display3(float lat2, float long2, float heading);
  void lat2Display(float lat2);
  void long2Display(float long2);
  void headingDisplay(float heading);
  void head3Display();

  private:
  float mHeadingDegree;
};
#endif
