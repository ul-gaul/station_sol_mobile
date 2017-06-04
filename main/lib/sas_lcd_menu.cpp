/*
    Menu class used to display the data in the watch rocket menu
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#include "sas_lcd_menu.h"

DisplayMenu::DisplayMenu(){
}

void DisplayMenu::main_menu(String current_menu){
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

void DisplayMenu::watch_rocket_menu(float altitude, float accelx, float accely, float accelz){
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

void DisplayMenu::find_rocket_menu(float distance, float rocketAngle, float northAngle){
    GLCD.ClearScreen();
    GLCD.CursorTo(0, 0);
    GLCD.print("Find Rocket");
    GLCD.CursorTo(0, 1);
    GLCD.print("Distance to rocket: ");
    GLCD.print(distance);
    GLCD.CursorTo(0,2);
    GLCD.print("Rocket angle from north: ");
    GLCD.print(rocketAngle);
    GLCD.CursorTo(0,3);
    GLCD.print("Angle to north");
    GLCD.print(northAngle);
}
