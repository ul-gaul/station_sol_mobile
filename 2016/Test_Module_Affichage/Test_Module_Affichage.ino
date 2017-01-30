#define TEST_ROCKET_PACKET false

#include "affichage.h"
#include "boutonSol.h"
#include "Compas.h"
#include"GPS.h"
#include"SerialPort.h"
#include"fctSol.h"
#include "acquisitionLogger.h"
#include "rocketData.h"
#include "serialPort.h"
#include "transceiver.h"
#include "TimerOne.h"

#define DISPLAY_TIME_INTERVAL 200

#define LOG_TIME_INTERVAL 1000
#define SD_CS_PIN 53 
#define SYSTEM_TYPE "r"

#define ORDI_PORT_NB 0
#define ORDI_BAUD_RATE 9600
#define RFD_PORT_NB 1 
#define RFD_BAUD_RATE 57600
#define GPS_PORT_NB 2
#define GPS_BAUD_RATE 9600

#define BTN_1 49
#define BTN_2 47
#define BTN_3 45
#define BTN_4 43


#define MAG_DECLINAISON 0.1745

affichage LCD;
fctSol fctSol;

boutonSol btnSol(BTN_1, BTN_2, BTN_3, BTN_4, HIGH);

Compas compas(MAG_DECLINAISON);
SerialPort ordiPort(ORDI_PORT_NB, ORDI_BAUD_RATE);
SerialPort RFDPort(RFD_PORT_NB, RFD_BAUD_RATE);
SerialPort GPSPort(GPS_PORT_NB, GPS_BAUD_RATE);
GPS GPS(GPSPort,0);

RocketPacket oldRocketPacket;
RocketPacket rocketPacket;
AcquisitionLogger sdLogger(SD_CS_PIN, SYSTEM_TYPE);

Transceiver transceiver;

int menu = 1;
int ancienMenu;

int btn;
bool oldBtn = false;
int aFaire;
int action;

int pos=1;

unsigned short sat;
float Lat;
float Long;
bool coordManuel;

bool SDe=true;
bool RFD=false;

float maxAlt = 0;

long temps_affichage = millis();
long temps_SDLogger  = millis(); 

long timeStampPrecedent;
float altitudePrecedente;

long tempsUpdate;

bool valueUpToDate = false;

void setup() 
{
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  compas.init();
  ordiPort.begin();
  RFDPort.begin();
  GPSPort.begin();
  Serial.println("Début");
  //Init SD card
  if (!sdLogger.initCard())
  {
    SDe=false;
  }
  sdLogger.writeHeader();
  pinMode(40,OUTPUT);

  Timer1.initialize(1000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

//                                         CODE PRINCIPAL
void loop() 
{
//Réception des données
  oldRocketPacket = rocketPacket;
  rocketPacket = transceiver.receiveRocketPacket(rocketPacket, RFDPort);
//  if(oldRocketPacket.rocketData.timeStamp != rocketPacket.rocketData.timeStamp) {
    SDLog();
    Serial.print("timestamp: ");
    Serial.println(rocketPacket.rocketData.timeStamp);
//  }

if(valueUpToDate == false) {
  GPS.updateCoord(GPSPort);
  sat=GPS.getConnection();

//  if (rocketPacket.rocketData.altitude > maxAlt) {
//    maxAlt = rocketPacket.rocketData.altitude;
//  }

  //Écriture des données dans la carte SD
  valueUpToDate = true;
}
//transceiver.sendRocketPacket(rocketPacket, ordiPort);



//Regarder les commandes de l'utilisateur
//getAction();
/*
//Afficher sur l'écran LCD
faireAffichage(menu);
*/
}

void timerIsr() {
  valueUpToDate = false;
}

void faireAffichage(int mMenu){
if ((millis()-temps_affichage) > DISPLAY_TIME_INTERVAL || menu != ancienMenu){
  switch(mMenu){
    
    case 1:
    LCD.displayAccueil();
    ancienMenu=1;
    break;
    
    case 2:
    LCD.displayData(getVSI(), rocketPacket.rocketData.accelZ, maxAlt, rocketPacket.rocketData.altitude);
    ancienMenu=2;
    break;

    case 3:
    LCD.displayData2(rocketPacket.rocketData.latitude1, rocketPacket.rocketData.longitude1, rocketPacket.rocketData.temperature1, rocketPacket.rocketData.temperature2);
    ancienMenu=3;
    break;

    case 4:
    //GPS.updateCoord(GPSPort);
    if (!LCD.getManuelCoord()){
      LCD.displayTracking(compas.getNorthAngle()-GPS.courseTo(GPS.getLat(), GPS.getLong(),rocketPacket.rocketData.latitude1, rocketPacket.rocketData.longitude1), compas.getNorthAngle(), GPS.getDistance(rocketPacket.rocketData.latitude1, rocketPacket.rocketData.longitude1, GPS.getLat(), GPS.getLong()));
    }
    else {
      LCD.displayTracking(compas.getNorthAngle()-GPS.courseTo(GPS.getLat(), GPS.getLong(),LCD.getManuelLat(), LCD.getManuelLong()), compas.getNorthAngle(), GPS.getDistance(LCD.getManuelLat(), LCD.getManuelLong(), GPS.getLat(), GPS.getLong()));
    }
    ancienMenu=4;
    break;

    case 5:
    coordManuel=LCD.displayTracking2(pos,aFaire);
    aFaire=0;
    ancienMenu=5;
    break;

    case 6:
    //GPS.updateCoord(GPSPort);
    //sat = GPS.getConnection();
    LCD.displayConnection(SDe, compas.getEtat(), RFD, sat);
    ancienMenu=6;
    Serial.print("I'm ok!");
    break;

    case 7:
    GPS.updateCoord(GPSPort);
    LCD.displayData3(GPS.getLat(), GPS.getLong(), compas.getNorthAngle());
    ancienMenu=7;  
  }
temps_affichage=millis();
}
}

void getAction(){
btn=btnSol.getPress();
if (btn != 0 && !oldBtn)
{
  digitalWrite(40,HIGH);
  oldBtn = true;
  action = fctSol.doFct(menu,btn);
  switch(action) {
    case 1:
      menu=1;
    break;
    case 2:
      menu=2;
    break;
    case 3:
      menu=3;
    break;
    case 4:
      menu=4;
    break;
    case 5:
      menu=5;
    break;
    case 6:
      aFaire=6;
    break;
    case 7:
      aFaire=7;
    break;
    case 8:
      menu=6;
    break;
    case 9:
      pos+=1;
      if (pos>14) {
        pos=1;
      }
    break;
    case 10:
      aFaire=10;
    break;
    case 11:
      aFaire=11;
    break;
    case 12:
      menu=7;
    break;
  }
}
else if(btn==0 && oldBtn) {
  digitalWrite(40,LOW);
  oldBtn = false;
}
}

void SDLog()
{
  if (millis()-temps_SDLogger >= LOG_TIME_INTERVAL)
  {
    sdLogger.writeRocketData(rocketPacket);
    temps_SDLogger=millis();
  }
}

float getVSI() 
{
  float VSI = 0;
  if(rocketPacket.rocketData.timeStamp-timeStampPrecedent != 0)
  {
    VSI=(rocketPacket.rocketData.altitude-altitudePrecedente)/(rocketPacket.rocketData.timeStamp-timeStampPrecedent)*1000;
  }
  return VSI;
}

