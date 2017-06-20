/*
    Menu class used to display the data in the watch rocket menu
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#ifndef _menu_watch_rocket_h
#define _menu_watch_rocket_h_h

#include "Menu.h"

class MenuWatchRocketLCD: public Menu
{
public:
    void display_data(float altitude, float accelx, float accely, float accelz);

}
