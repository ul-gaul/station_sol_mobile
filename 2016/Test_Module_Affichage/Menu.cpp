/*
  Compas.cpp - Librarie pour le compas utilite avec la station au sol Arduino 2016.
  Creer par Alex Tourigny-Plante et Simon Belley, 24 fevrier 2016.
  Propriete du Groupe aerospatial de l'Universite Laval.
*/
#include "Menu.h"
void Menu::drawBox()
{
    GLCD.DrawRect(0,52,(GLCD.Width)/4,11);
    GLCD.DrawRect(32,52,(GLCD.Width)/4,11);
    GLCD.DrawRect(64,52,(GLCD.Width)/4,11);
    GLCD.DrawRect(96,52,(GLCD.Width)/4,11);
}
