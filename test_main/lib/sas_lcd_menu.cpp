/*
    Menu class used to display the data in the watch rocket menu
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#include "sas_lcd_menu.h"

sas_lcd_menu::sas_lcd_menu(){
}

void sas_lcd_menu::main_menu(String current_menu){
    GLCD.ClearScreen();
    GLCD.CursorTo(0, 0);
    GLCD.print("Main menu");
    GLCD.CursorTo(0, 1);
    GLCD.print("Bouton 1: OK");
    GLCD.CursorTo(0, 2);
    GLCD.print("Bouton 2: DOWN");
    GLCD.CursorTo(0, 3);
    GLCD.print("> ");
    GLCD.print(current_menu);
}

void sas_lcd_menu::watch_rocket_menu(float altitude, float accelx, float accely, float accelz){
    GLCD.ClearScreen();
    GLCD.CursorTo(0, 0);
    GLCD.print("Watch Rocket");
    GLCD.CursorTo(0, 1);
    GLCD.print("Altitude: ");
    GLCD.print(altitude);
    GLCD.CursorTo(0,2);
    GLCD.print("Acceleration X: ");
    GLCD.print(accelx);
    GLCD.CursorTo(0,3);
    GLCD.print("Acceleration Y: ");
    GLCD.print(accely);
    GLCD.CursorTo(0, 4);
    GLCD.print("Acceleration Z: ");
    GLCD.print(accelz);
}

void sas_lcd_menu::find_rocket_menu(float distance, float rocketAngle, float northAngle){
    GLCD.ClearScreen();
    GLCD.CursorTo(0, 0);
    GLCD.print("Find Rocket");
    GLCD.CursorTo(0, 1);
    GLCD.print("Distance: ");
    GLCD.print(distance);
    GLCD.CursorTo(0,2);
    GLCD.print("Rocket angle: ");
    GLCD.print(rocketAngle);
    GLCD.CursorTo(0,3);
    GLCD.print("North angle: ");
    GLCD.print(northAngle);
}
