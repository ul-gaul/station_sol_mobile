// test program for the LCD screen

#include "lib/acquisitionLogger.h"
#include "lib/Compas.h"
#include "lib/rocketData.h"
#include "lib/serialPort.h"
#include "lib/TinyGPS.h"
#include "lib/transceiver.h"
#include "lib/Menu.h"
#include "Arduino.h"
#include "openGLCD.h"
#include <fonts/allFonts.h>
#include "lib/sas_lcd_menu.h"

// Pin definitions
#define RFD_PORT_NB 1
#define RFD_BAUDRATE 57600
#define GPS_PORT_NB 2
#define GPS_BAUDRATE 9600
// pin SDA 20
// pin SCL 21 pour le Compas
#define LCD_D0 22
#define LCD_D1 23
#define LCD_D2 24
#define LCD_D3 25
#define LCD_D4 26
#define LCD_D5 27
#define LCD_D6 28
#define LCD_D7 29
#define LCD_CS1 34
#define LCD_CS2 33
#define LCD_RW 35
#define LCD_RS 36
#define LCD_E 37

DisplayMenu myMenu();

void setup(){
    // Initialize the GLCD
    GLCD.Init();
    // Select the font for the default text area
    GLCD.SelectFont(System5x7);
    GLCD.ClearScreen();
    myMenu.main_menu("Watch Rocket");
    delay(1000);
}

void loop(){
    myMenu.watch_rocket_menu(3000, 1, 2, 9.8);
    delay(1000)
    myMenu.find_rocket_menu(1000, 30, 180);
}
