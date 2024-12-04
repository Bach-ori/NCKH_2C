#ifndef Button_H
#define Button_H

#include <esp_timer.h>

//IO button
const uint8_t buttonPin_1 = 10; 
const uint8_t buttonPin_2 = 11; 
const uint8_t buttonPin_3 = 12; 
const uint8_t buttonPin_4 = 13; 

//State button
volatile bool buttonPressed[4] = {false,false,false,false};

volatile unsigned long lastDebounceTime_1 = 0;
volatile unsigned long lastDebounceTime_2 = 0;
volatile unsigned long lastDebounceTime_3 = 0;
volatile unsigned long lastDebounceTime_4 = 0;
const unsigned long debounceDelay = 300; 

bool check_time_mode = false;

bool State_bt = false;

void IRAM_ATTR buttonISR_1()   
{
  unsigned long currentMillis = esp_timer_get_time();
  if ((currentMillis - lastDebounceTime_1 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_1 = currentMillis;
    buttonPressed[0] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_2()   
{
  unsigned long currentMillis = esp_timer_get_time();
  if ((currentMillis - lastDebounceTime_2 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_2 = currentMillis;
    buttonPressed[1] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_3()  
{
unsigned long currentMillis = esp_timer_get_time();
  if ((currentMillis - lastDebounceTime_3 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_3 = currentMillis;
    buttonPressed[2] = true;
    State_bt = true;
  }
}

void IRAM_ATTR buttonISR_4()  
{
  unsigned long currentMillis = esp_timer_get_time();
  if ((currentMillis - lastDebounceTime_4 > debounceDelay) && !State_bt) 
  {
    lastDebounceTime_4 = currentMillis;
    buttonPressed[3] = true;
    State_bt = true;
  }
}

void setup_button()
{
  pinMode(buttonPin_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_1), buttonISR_1, FALLING);

  pinMode(buttonPin_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_2), buttonISR_2, FALLING);

  pinMode(buttonPin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_3), buttonISR_3, FALLING);

  pinMode(buttonPin_4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_4), buttonISR_4, FALLING);
}

#endif