#include "accueilDisplay.h"

void AccueilDisplay::display1()
{
  textDisplay();
  boutonDisplay();
  drawBox();
}

void AccueilDisplay::textDisplay()
{
  GLCD.CursorToXY(6,0);
  GLCD.print("Menu Principal");
  GLCD.CursorToXY(6,10);
  GLCD.print("1 :");
  GLCD.CursorToXY(6,20);
  GLCD.print("2 :");
  GLCD.CursorToXY(6,30);
  GLCD.print("3 :");
  GLCD.CursorToXY(6,40);
  GLCD.print("4 :");
  
  GLCD.CursorToXY(30,10);
  GLCD.print("Donnees de vol");
  GLCD.CursorToXY(30,20);
  GLCD.print("Donnees autres");
  GLCD.CursorToXY(30,30);
  GLCD.print("Reperage");
  GLCD.CursorToXY(30,40);
  GLCD.print("Connections");
}



void AccueilDisplay::boutonDisplay()
{
  GLCD.CursorToXY(14,54);
  GLCD.print("1");
  GLCD.CursorToXY(46,54);
  GLCD.print("2");
  GLCD.CursorToXY(78,54);
  GLCD.print("3");
  GLCD.CursorToXY(110,54);
  GLCD.print("4");
}
