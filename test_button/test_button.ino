#include "Arduino.h"

#define BTN_1 43
#define BTN_2 45
#define BTN_3 3
#define BTN_4 2

void int_button1_pressed(){
    Serial.println("btn1_ispressed");
}
void int_button2_pressed(){
    Serial.println("btn2_ispressed");
}
void int_button3_pressed(){
    Serial.println("btn3_ispressed");
}
void int_button4_pressed(){
    Serial.println("btn4_ispressed");
}

void setup(){
    Serial.begin(9600);
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_1), int_button1_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_2), int_button2_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_3), int_button3_pressed, RISING);
    attachInterrupt(digitalPinToInterrupt(BTN_4), int_button4_pressed, RISING);
}

void loop(){

}
