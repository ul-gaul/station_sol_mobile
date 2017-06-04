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
#define PI 3.141593



Transceiver RFD_RX;
RocketPacket rpktRX;
TinyGPS gps;
SerialPort serialGPS(GPS_PORT_NB, GPS_BAUDRATE);
bool newData = false;

// UART declarations for RFD900
SerialPort serial_RX(RFD_PORT_NB, RFD_BAUDRATE);
// Declarations for Compass
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
sensors_event_t compass_mag_event;
float north_angle = 0;
float rocket_angle = 0;
float bts_latitude = 0;
float bts_longitude = 0;
float rocket_latitude = 0;
float rocket_longitude = 0;
float distance_to_rocket;
//Declarations for SD card
AcquisitionLogger sdLogger(SD_CHIP_SELECT, SYSTEM_TYPE);
bool test_init_sd = false;

// Declarations for menus
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

float get_north_angle(){
    sensors_event_t event;
    mag.getEvent(&event);
    north_angle = atan2(event.magnetic.y, event.magnetic.x);
    north_angle += MAG_DECLINAISON;
    if(north_angle < 0){
        north_angle += 2*PI;
    }
    else if(north_angle > 2*PI){
        north_angle -= 2*PI;
    }
    return north_angle;
}

/* Donne l'angle à partir du nord pour rejoindre la cible */
float get_rocket_angle(float lat1, float lon1, float lat2, float lon2, float north_angle) {
    float RocketAngle = atan2(abs(lon1 - lon2), abs(lat1 - lat2));
    if(lon2 > lon1){
        RocketAngle = (PI / 2) - RocketAngle;
    }
    else{
        RocketAngle = (PI / 2) + RocketAngle;
    }
    if(lat2 > lat1){
        RocketAngle = north_angle + RocketAngle;
    }
    else{
        RocketAngle = north_angle - RocketAngle;
    }
    return RocketAngle;
}

void Get_Position (){
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
        while (serialGPS.available())
        {
            char c = serialGPS.read();
            if (gps.encode(c))
            {
                newData = true;
            }
        }
        if (newData)
        {
            unsigned long age;
            gps.f_get_position(&bts_latitude, &bts_longitude, &age);
        }
    }
}

/* function used to get the distance between the rocket and the base station */
float get_distance_to_rocket(float lat1, float long1, float lat2, float long2) {
    distance_to_rocket = gps.distance_between(lat1, long1, lat2, long2);
    if (distance_to_rocket > 100000) {
    return 999;
    }
    return distance_to_rocket;
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
    Serial.println("Btn1: OK, Btn2: DOWN");
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
            set_all_buttons_false();
        }
        if(btn3_ispressed){
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
    }
}

/* function for the menu that allows to watch te Rocket's flight */
void watch_rocket_menu(menu* p_menu){
    Serial.println("Watch Rocket Menu");
    Serial.println("Press back to go to main menu");
    Serial.println("Press find to go to find rocket menu");
    Serial.println("BACK: btn1");
    Serial.println("FIND: btn2");
    while (1){
        // Receive RocketPackets
        rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
        // Log data in SD card
        sdLogger.writeRocketData(rpktRX);
        // Display rocket data
        // Interresting data is: altitude, acceleration XYZ
        Serial.print("Altitude: ");
        Serial.println(rpktRX.rocketData.altitude);
        Serial.print("Accel X: ");
        Serial.println(rpktRX.rocketData.accelX);
        Serial.print("Accel Y: ");
        Serial.println(rpktRX.rocketData.accelY);
        Serial.print("Accel Z: ");
        Serial.println(rpktRX.rocketData.accelZ);

        if(btn1_ispressed){
            // Back to main menu button
            Serial.println("button BACK pressed");
            *p_menu = MAIN;
            set_all_buttons_false();
            break;
        }
        if(btn2_ispressed){
            // Go to find rocket menu
            Serial.println("button FIND pressed");
            *p_menu = FIND_ROCKET;
            set_all_buttons_false();
            break;
        }
    }
}

void find_rocket_menu(menu* p_menu){
    Serial.println("Find Rocket Menu");
    Serial.println("Press back to go to main menu");
    Serial.println("Press watch to go to watch rocket menu");
    Serial.println("BACK: btn1, WATCH: btn2");
    while (1){
        // Receive RocketPackets
        rpktRX = RFD_RX.receiveRocketPacket(rpktRX, serial_RX);
        // Log data in SD card
        sdLogger.writeRocketData(rpktRX);
        // Display rocket data
        // Interesting to find rocket is: distance from rocket, direction to
        // rocket
        // Get_Position();
        unsigned long age;
        for (unsigned long start = millis(); millis() - start < 1000;)
        {
            while (serialGPS.available())
            {
                char c = serialGPS.read();
                // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
                if (gps.encode(c)) { // Did a new valid sentence come in?
                    newData = true;
                }
            }
        }

        if(newData){
            rocket_latitude = rpktRX.rocketData.latitude1;
            rocket_longitude = rpktRX.rocketData.longitude1;
            gps.f_get_position(&bts_latitude, &bts_longitude, &age);
            Serial.print("BTS lat: ");
            Serial.println(bts_latitude);
            Serial.print("BTS lon: ");
            Serial.println(bts_longitude);
        }
        distance_to_rocket = get_distance_to_rocket(bts_latitude, bts_longitude, rocket_latitude, rocket_longitude);
        Serial.print("Distance to rocket is: ");
        Serial.println(distance_to_rocket);
        north_angle = get_north_angle();
        Serial.print("Angle to north is: ");
        Serial.println(north_angle*180/PI);
        rocket_angle = get_rocket_angle(bts_latitude, bts_longitude, rocket_latitude, rocket_longitude, north_angle);
        Serial.print("Angle to rocket from north is: ");
        Serial.println(rocket_angle*180/PI);
        if(btn1_ispressed){
            // Back to main menu button
            Serial.println("button BACK pressed");
            *p_menu = MAIN;
            set_all_buttons_false();
            break;
        }
        if(btn2_ispressed){
            // Go to watch rocket menu
            Serial.println("button WATCH pressed");
            *p_menu = WATCH_ROCKET;
            set_all_buttons_false();
            break;
        }
    }
}

void setup(){
//    noInterrupts();
    Serial.begin(9600);
    Serial.println("Setup begin");
    serial_RX.begin();
    serialGPS.begin();
    mag.begin();
    // Serial2.begin();
    Log_Start();
    // Init SD card
    bool test_sd_card = false;
    while(!test_init_sd){
        test_init_sd = sdLogger.initCard();
        if(!test_init_sd){
            Serial.println("SD card init failed");
        } else {
            Serial.println("SD card init sucess");
        }
    }
    sdLogger.writeHeader();
    // attach interrupt for buttons
    // interrupts();
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_1), int_button1_pressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_2), int_button2_pressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_3), int_button3_pressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_4), int_button4_pressed, FALLING);
    Serial.println("Setup end");
}

void loop(){

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
