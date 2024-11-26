#ifndef Button_H
#define Button_H

#include <Arduino.h>
#include "Var.h"

//IO button
const uint8_t buttonPin_1 = 1; 
const uint8_t buttonPin_2 = 2; 
const uint8_t buttonPin_3 = 3; 
const uint8_t buttonPin_4 = 4; 

//State button
volatile bool buttonPressed[4] = {false,false,false,false};

volatile unsigned long lastDebounceTime_1 = 0;
volatile unsigned long lastDebounceTime_2 = 0;
volatile unsigned long lastDebounceTime_3 = 0;
volatile unsigned long lastDebounceTime_4 = 0;
const unsigned long debounceDelay = 300; // Thời gian chờ để xử lý nhiễu (milliseconds)

bool check_time = false;
unsigned long startMillis;

bool State_bt = false;

void IRAM_ATTR buttonISR_1()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if ((currentMillis - lastDebounceTime_1 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_1 = currentMillis;
    buttonPressed[0] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_2()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if ((currentMillis - lastDebounceTime_2 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_2 = currentMillis;
    buttonPressed[1] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_3()   //chuyển chế độ 
{
unsigned long currentMillis = millis();
  if ((currentMillis - lastDebounceTime_3 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_3 = currentMillis;
    buttonPressed[2] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_4()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if ((currentMillis - lastDebounceTime_4 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_4 = currentMillis;
    buttonPressed[3] = true;
    State_bt = true;
  }
}

#endif


