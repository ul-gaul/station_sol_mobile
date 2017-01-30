#include "trackingdisplay.h"

void TrackingDisplay::display1(float trackAngle,float northAngle,float distance)
{
  bouton1Display();
  drawBox();
  compassDisplay(trackAngle, northAngle);
  nDisplay(northAngle);
  sDisplay(northAngle);
  eDisplay(northAngle);
  wDisplay(northAngle);
  distanceDisplay(distance);
	}

void TrackingDisplay::bouton1Display()
{
     GLCD.CursorToXY(6,54);
        GLCD.print("set.");
        GLCD.DrawLine(32,52,32+((GLCD.Width)/4),52+10);
        GLCD.DrawLine(32,52+10,32+((GLCD.Width)/4),52);
        GLCD.DrawLine(64,52,64+((GLCD.Width)/4),52+10);
        GLCD.DrawLine(64,52+10,64+((GLCD.Width)/4),52);
        GLCD.CursorToXY(100,54);
        GLCD.print("back");
}

void TrackingDisplay::compassDisplay(float anglesuivre, float northAngle)
{
	GLCD.DrawCircle(62,25,15,BLACK); // Dessin du cercle avec les coordonnées du centre en x y , du rayon et de la coulleur
    GLCD.DrawLine(62,25,coordonneesXD(anglesuivre),coordonneesYD(anglesuivre)); // Dessin du pointeur avec les coordonnées x y du départ et les coordonnées x y de fin
    GLCD.DrawLine(62,10,58,16);
    GLCD.DrawLine(62,10,66,16);

}
void TrackingDisplay::distanceDisplay(float distance)
{
	GLCD.CursorToXY(91 , 5);
    GLCD.print("dist:");
    GLCD.CursorToXY(91 , 15);
    GLCD.print(distance);
}
void TrackingDisplay::nDisplay(float angle)
{
	GLCD.CursorToXY (coordonneesXN(angle), coordonneesYN(angle));  // affichage du nord
        GLCD.Puts("N");
}
void TrackingDisplay::sDisplay(float angle)
{
	GLCD.CursorToXY (coordonneesXN(angle + PI), coordonneesYN(angle+ PI)); // affichage du sud à 180 degré du nord
        GLCD.Puts("S");

}
void TrackingDisplay::eDisplay(float angle)
{	GLCD.CursorToXY (coordonneesXN(angle - (PI/2)), coordonneesYN(angle - (PI/2))); // affichage de l'ouest à 90 degré du Sud
        GLCD.Puts("E");

}
void TrackingDisplay::wDisplay(float angle)
{
	GLCD.CursorToXY (coordonneesXN(angle + (PI/2)), coordonneesYN(angle + (PI/2))); // affichage de l'est à 90 degré du Nord
    GLCD.Puts("O");
}



int TrackingDisplay::coordonneesXN(float angle)
{
    int result  = 21*sin(angle+PI) + 62-2 ;
    return result;
}

int TrackingDisplay::coordonneesYN(float angle)
{
    int result  = 21*cos(angle+PI) + 25-3 ;
    return result;
}

int TrackingDisplay::coordonneesXD(float angle)
{
    int result  = 15*sin(angle+PI)+62 ;
    return result;
}

int TrackingDisplay::coordonneesYD(float angle)
{

    int result  = 15*cos(angle+PI)+ 25;
    return result;
}



void TrackingDisplay::display2(int pos)
{
  verify(mLat,mLong);
  bouton2Display();
  drawBox();
  GLCD.CursorToXY(6,0);
  GLCD.print("Parametre coordonnee");
  displayCoordManuel();
  invert(pos);
  displayLat(mLat);
  displayLong(mLong);
	}

void TrackingDisplay::verify(float lat, float lon)
{
  if (abs(lat)>90.000){
    mLat=00.000;
  }

  if (abs(lon)>180.000){
    mLong=000.000;
  }
}

void TrackingDisplay::invert(int pos)
{   
  if (pos==14) {
    GLCD.InvertRect(82,40+8,17,2);
  }
  else {
    y = 16+8;
    x2=0;
    if (pos>6) {
        y = 28+8;
        pos-=6;
        x2=-6;
    }
    x = 46+x2+6*(pos-1);
    if ((x)>=64){
        x+=6;
    }
    GLCD.InvertRect(x,y,5,2);
  }
}


void TrackingDisplay::bouton2Display()
{
 GLCD.CursorToXY(6,54);
    GLCD.print("next");
    GLCD.CursorToXY(45,54);
    GLCD.print("+");
    GLCD.CursorToXY(78,54);
    GLCD.print("-");
    GLCD.CursorToXY(100,54);
    GLCD.print("back");
}

void TrackingDisplay::incrementer(int pos)
{
    switch(pos){
    case 1 :
        if (mLatDirection == 1) {
          mLatDirection = -1;
        }
        else {
          mLatDirection = 1;
        }
        break;
    case 2 :
        mLat+=10.000;
        break;
    case 3 :
        mLat+=01.000;
        break;
    case 4 :
        mLat+=00.100;
        break;
    case 5 :
        mLat+=00.010;
        break;
    case 6 :
        mLat+=00.001;
        break;
    case 7 :
        if (mLongDirection == 1) {
          mLongDirection = -1;
        }
        else {
          mLongDirection = 1;
        }
        break;
    case 8 :
        mLong+=100.000;
        break;
    case 9 :
        mLong+=10.000;
        break;
    case 10 :
        mLong+=01.000;
        break;
    case 11 :
        mLong+=00.100;
        break;
    case 12 :
        mLong+=00.010;
        break;
    case 13 :
        mLong+=00.001;
        break;
    case 14:
        if(!mCoordManuel)
        {
            mCoordManuel=true;
        }
        else
        {
            mCoordManuel=false;
        }
        break;
    }
}

void TrackingDisplay::decrementer(int pos)
{
    switch(pos){
    case 1 :
        if (mLatDirection == 1) {
          mLatDirection = -1;
        }
        else {
          mLatDirection = 1;
        }
        break;
    case 2 :
        mLat-=10.000;
        break;
    case 3 :
        mLat-=01.000;
        break;
    case 4 :
        mLat-=00.100;
        break;
    case 5 :
        mLat-=00.010;
        break;
    case 6 :
        mLat-=00.001;
        break; 
    case 7 :
        if (mLongDirection == 1) {
          mLongDirection = -1;
        }
        else {
          mLongDirection = 1;
        }
        break;
    case 8 :
        mLong-=100.000;
    case 9 :
        mLong-=10.000;
        break;
    case 10 :
        mLong-=01.000;
        break;
    case 11 :
        mLong-=00.100;
        break;
    case 12 :
        mLong-=00.010;
        break;
    case 13 :
        mLong-=00.001;
        break;
    case 14:
        if(!mCoordManuel)
        {
            mCoordManuel=true;
        }
        else
        {
            mCoordManuel=false;
        }
        break;
    }
}

void TrackingDisplay::displayLat(float Lat)
{
    mDizaine = Lat/10;
    mUnite = (Lat-mDizaine*10)/1;
    mDixieme = (Lat-mDizaine*10-mUnite)/0.1;
    mCentieme = (Lat-mDizaine*10-mUnite-mDixieme*0.1)/0.01;
    mMillieme = (Lat-mDizaine*10-mUnite-mDixieme*0.1-mCentieme*0.01)/0.001;

    
    GLCD.CursorToXY(6,16);
    GLCD.print("Lat");
    GLCD.CursorToXY(28,16);
    GLCD.print(":");
    GLCD.CursorToXY(46,16);
    if (mLatDirection == 1){
      GLCD.print("+");
    }
    else {
      GLCD.print("-");
    }
    GLCD.CursorToXY(52,16);
    GLCD.print(mDizaine);
    GLCD.CursorToXY(58,16);
    GLCD.print(mUnite);
    GLCD.CursorToXY(64,16);
    GLCD.print(".");
    GLCD.CursorToXY(70,16);
    GLCD.print(mDixieme);
    GLCD.CursorToXY(76,16);
    GLCD.print(mCentieme);
    GLCD.CursorToXY(82,16);
    GLCD.print(mMillieme);
}

void TrackingDisplay::displayLong(float Long)
{
    mCentaine = Long/100;
    mDizaine = (Long-mCentaine*100)/10;
    mUnite = (Long-mCentaine*100-mDizaine*10)/1;
    mDixieme = (Long-mCentaine*100-mDizaine*10-mUnite)/0.1;
    mCentieme = (Long-mCentaine*100-mDizaine*10-mUnite-mDixieme*0.1)/0.01;
    mMillieme = (Long-mCentaine*100-mDizaine*10-mUnite-mDixieme*0.1-mCentieme*0.01)/0.001;

    GLCD.CursorToXY(6,28);
    GLCD.print("Long");
    GLCD.CursorToXY(30,28);
    GLCD.print(":");
    GLCD.CursorToXY(40,28);
    if (mLongDirection == 1){
      GLCD.print("+");
    }
    else {
      GLCD.print("-");
    }
    GLCD.CursorToXY(46,28);
    GLCD.print(mCentaine);
    GLCD.CursorToXY(52,28);
    GLCD.print(mDizaine);
    GLCD.CursorToXY(58,28);
    GLCD.print(mUnite);
    GLCD.CursorToXY(64,28);
    GLCD.print(".");
    GLCD.CursorToXY(70,28);
    GLCD.print(mDixieme);
    GLCD.CursorToXY(76,28);
    GLCD.print(mCentieme);
    GLCD.CursorToXY(82,28);
    GLCD.print(mMillieme);
}



float TrackingDisplay::getLat()
{
  return mLatDirection*mLat;
}

float TrackingDisplay::getLong()
{
  return mLongDirection*mLong;
}

bool TrackingDisplay::coordManuel()
{
    return mCoordManuel;
}

void TrackingDisplay::displayCoordManuel()
{
    GLCD.CursorToXY(6,40);
    GLCD.print("cette coord:");
    GLCD.CursorToXY(82,40);
    if (mCoordManuel)
    {
        GLCD.print("Yes");
    }
    else
    {
        GLCD.print("No");
    }
}
