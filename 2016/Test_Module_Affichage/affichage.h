
#ifndef affichage_h
#define affichage_h

#include "Arduino.h"
#include "connectionDisplay.h"
#include "datadisplay.h"
#include "trackingdisplay.h"
#include "accueilDisplay.h"

class affichage: public ConnectionDisplay, public DataDisplay, public TrackingDisplay, public AccueilDisplay, public Menu
{ public:
    affichage();
    void displayConnection(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat);
    void displayData(float speed,float acceleration,float temperature,float height);
    void displayData2(float lat1, float long1, float temperature1, float temperature2);
    void displayData3(float lat2, float long2, float heading);
    void displayTracking(float trackAngle,float northAngle,float distance);
    void displayAccueil();
    bool displayTracking2(int pos,int action);
    
    ConnectionDisplay connectionDisplay;
    DataDisplay dataDisplay;
    TrackingDisplay trackingDisplay;
    AccueilDisplay accueilDisplay;
    float getManuelLat();
    float getManuelLong();
    bool getManuelCoord();
  private:
  bool mCoord;


};

#endif

