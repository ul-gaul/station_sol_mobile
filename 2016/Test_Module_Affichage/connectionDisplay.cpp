#include "connectionDisplay.h"

void ConnectionDisplay::display1(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat)
{
    textDisplay(SDEtat,CompasEtat,RFDEtat,sat);
    boutonDisplay();

}

void ConnectionDisplay::textDisplay(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat)
{
	GLCD.CursorToXY(6,1);
        GLCD.print("Affichage des etats");
    GLCD.CursorToXY(6,10);
        GLCD.print("- Carte SD");
    GLCD.CursorToXY(6,20);
        GLCD.print("- Compas");
    GLCD.CursorToXY(6,30);
        GLCD.print("- RFD");
      GLCD.CursorToXY(6,40);
        GLCD.print("- Nb de sat");

      GLCD.CursorToXY(75,10);
        GLCD.print(":");
      GLCD.CursorToXY(75,20);
        GLCD.print(":");
      GLCD.CursorToXY(75,30);
        GLCD.print(":");
      GLCD.CursorToXY(75,40);
        GLCD.print(":");

      GLCD.CursorToXY(100,10);
        etatDisplay(SDEtat);
      GLCD.CursorToXY(100,20);
        etatDisplay(CompasEtat);
      GLCD.CursorToXY(100,30);
        etatDisplay(RFDEtat);
      GLCD.CursorToXY(100,40);
        satDisplay(sat);
}

void ConnectionDisplay::etatDisplay(bool etat)
{
      if(etat)
      {
        GLCD.print("ok");
      }
      else
      {
        GLCD.print("X");
      }
}
void ConnectionDisplay::satDisplay(unsigned short sat)
{
  GLCD.print(sat);
}

void ConnectionDisplay::boutonDisplay()
{
     GLCD.CursorToXY(6,54);
        GLCD.print("Press to go back...");
}
