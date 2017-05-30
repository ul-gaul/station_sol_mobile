/*
    Programme principal pour l'acquisition de données de la station au sol
    du GAUL - 2017.
    Ver.    0.1
    Simon Bellemare
    Samuel Côté
    Maxime Guillemette
*/

#include "lib/acquisitionLogger.h"
#include "lib/Compas.h"
#include "lib/rocketData.h"
#include "lib/serialPort.h"
#include "lib/TinyGPS.h"
#include "lib/transceiver.h"
#include "Arduino.h"

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
#define BTN_1 2
#define BTN_2 3
#define BTN_3 45
#define BTN_4 43
// carte SD: MISO 50
// MOSI 51, SCK 52, CS 53
#define SD_CHIP_SELECT 53


#define MAG_DECLINAISON 0
#define LOG_TIME_INTERVAL 1000
#define SYSTEM_TYPE "r"

float northAngle = 0;
float latitude = 0;
float longitude = 0;


Transceiver RFD_RX;
RocketPacket rpktRX;
TinyGPS gps;
bool newData = false;

SerialPort serial_RX(RFD_PORT_NB, RFD_BAUDRATE);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
AcquisitionLogger sdLogger(SD_CHIP_SELECT, SYSTEM_TYPE);
bool test_init_sd = false;


/* ============================================================================
        DECLARATIONS FOR MENUS
============================================================================*/
typedef enum menu {MAIN, WATCH_ROCKET, FIND_ROCKET} menu;
#define SUBMENU_TABLE_SIZE 2
// Array of menus that can be selected from the main menu
menu submenu_table[SUBMENU_TABLE_SIZE] = {WATCH_ROCKET, FIND_ROCKET};

menu current_menu = MAIN;

bool btn1_ispressed = false;
bool btn2_ispressed = false;
bool btn3_ispressed = false;
bool btn4_ispressed = false;

void Log_Start(){
    while(!test_init_sd){
      test_init_sd = sdLogger.initCard();
    }
    sdLogger.writeHeader();
}

void Log_Rocket_Data(){
    if (serial_RX.available()){
      rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
      sdLogger.writeRocketData(rpktRX);
    }
}

void Get_North_Angle(){
    sensors_event_t event;
    mag.getEvent(&event);
    northAngle = atan2(event.magnetic.y, event.magnetic.x);
    northAngle += MAG_DECLINAISON;
    if(northAngle < 0){
        northAngle += 2*PI;
    }
    else if(northAngle > 2*PI){
        northAngle -= 2*PI;
    }
}

void Get_Position (){
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
        while (Serial2.available())
        {
            char c = Serial2.read();
            if (gps.encode(c))
            {
                newData = true;
            }
        }
        if (newData)
        {
            unsigned long age;
            gps.f_get_position(&latitude, &longitude, &age);
        }
    }
}

/* interrupt service routine for when button 1 is pressed */
void int_button1_pressed(){
    Serial.println("btn1 pressed!");
    btn1_ispressed = true;
}

/* interrupt service routine for when button 2 is pressed */
void int_button2_pressed(){
    Serial.println("btn2 pressed!");
    btn2_ispressed = true;
}

/* interrupt service routine for when button 3 is pressed */
void int_button3_pressed(){
    Serial.println("btn3 pressed!");
    btn3_ispressed = true;
}

/* interrupt service routine for when button 4 is pressed */
void int_button4_pressed(){
    Serial.println("btn4 pressed!");
    btn4_ispressed = true;
}

/* function to set all button_is_pressed variables to false */
void set_all_buttons_false(){
    btn1_ispressed = false;
    btn2_ispressed = false;
    btn3_ispressed = false;
    btn4_ispressed = false;
}

/* function for the main menu */
void main_menu(menu* p_menu, menu submenu_table[SUBMENU_TABLE_SIZE]){
    // list of menus to select from
    int index = 0;
    menu selected_menu = submenu_table[index];
    Serial.println("MAIN MENU\n");
    Serial.println("Watch rocket\nFind Rocket\nPress ok to select a menu");
    // interrupts();
    while (1){
        if(btn1_ispressed){
            // button OK
            // selected menu is confirmed
            Serial.println("button OK pressed");
            *p_menu = selected_menu;
            set_all_buttons_false();
            // noInterrupts();
            break;
        }
        if(btn2_ispressed){
            // button UP
            // change selected menu UP
            Serial.println("button UP pressed");
            Serial.print("index is: ");
            Serial.println(index);
            if(index == 0){
                index = SUBMENU_TABLE_SIZE - 1;
                selected_menu = submenu_table[index];
            } else {
                index--;
                selected_menu = submenu_table[index];
            }
        }
        if(btn3_ispressed){
            // button DOWN
            // change selected menu DOWN
            Serial.println("button DOWN pressed");
            Serial.print("index is: ");
            Serial.println(index);
            if(index == SUBMENU_TABLE_SIZE - 1){
                index = 0;
                selected_menu = submenu_table[index];
            } else {
                index++;
                selected_menu = submenu_table[index];
            }
        }
    }
}

void watch_rocket_menu(menu* p_menu){
    // interrupts();
    while (1){

    }
}

void find_rocket_menu(menu* p_menu){
    // interrupts();
    while (1){

    }
}

void setup(){
//    noInterrupts();
    Serial.begin(9600);
    Serial.println("commencement de la vie");
    serial_RX.begin();
    mag.begin();
    // Serial2.begin();
    Log_Start();
    // attach interrupt for buttons
    // interrupts();
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_1), int_button1_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_2), int_button2_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_3), int_button3_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_4), int_button4_pressed, RISING);
    Serial.println("le cercle de la vie commence");
}

void loop(){
    /*
    Log_Rocket_Data();  //Receives Data from the rocket and logs it into the SD card
    Get_North_Angle();  //Gets the orientation of the base station
    Get_Position();     //Gets the position of the base station
    */

    Serial.println("switching menus");
    switch(current_menu){

        case MAIN:
            Serial.println("main case");
            main_menu(& current_menu, submenu_table);
            break;

        case WATCH_ROCKET:
            Serial.println("watch rocket case");
            watch_rocket_menu(& current_menu);
            break;

        case FIND_ROCKET:
            Serial.println("find_rocket case");
            find_rocket_menu(& current_menu);
            break;

        default:
            // reset to MAIN
            Serial.println("default case");
            current_menu = MAIN;
            break;
    }
}
