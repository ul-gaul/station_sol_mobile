#ifndef _trackingdisplay_h
#define _trackingdisplay_h_h

#include "Menu.h"
class TrackingDisplay: public Menu
{	public:
	void display1(float trackAngle,float northAngle,float distance);
	void bouton1Display();
	void bouton2Display();
	void compassDisplay(float anglesuivre, float northAngle);
    void distanceDisplay(float distance);
	void nDisplay(float angle);
	void sDisplay(float angle);
	void eDisplay(float angle);
	void wDisplay(float angle);
	int coordonneesXN(float angle);
	int coordonneesYN(float angle);
	int coordonneesXD(float angle);
	int coordonneesYD(float angle);
	void display2(int pos);
	void displayLat(float Lat);
	void displayLong(float Long);
	void incrementer(int pos);
	void decrementer(int pos);
	void invert(int pos);
	void displayCoordManuel();
	float getLat();
	float getLong();
	bool coordManuel();
 void verify(float lat, float lon);
	private:
    float mLat;
    float mLong;
    int mLatDirection = 1;
    int mLongDirection = 1;
    int mCentaine;
    int mDizaine;
    int mUnite;
    int mDixieme;
    int mCentieme;
    int mMillieme;
    int x;
    int x2;
    int y;
    bool mCoordManuel;
};
#endif
