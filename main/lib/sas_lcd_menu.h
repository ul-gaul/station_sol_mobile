/*
    Menu class used to display the data in the watch rocket menu
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#ifndef _sas_lcd_menu_h
#define _sas_lcd_menu_h_h

#include "Arduino.h"
#include "openGLCD.h"
#include <fonts/allFonts.h>


class DisplayMenu
{
public:
    DisplayMenu();
    void main_menu(String current_menu);
    void watch_rocket_menu(float altitude, float accelx, float accely, float accelz);
    void find_rocket_menu(float distance, float rocketAngle, float northAngle);
}


#endif
