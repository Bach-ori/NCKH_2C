#ifndef Button_H
#define Button_H

#include <Arduino.h>
#include "Var.h"

void IRAM_ATTR buttonISR_1()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_1 > debounceDelay) 
  {
    lastDebounceTime_1 = currentMillis;
    buttonPressed_1 = true;
  }
}

void IRAM_ATTR buttonISR_2()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_2 > debounceDelay) 
  {
    lastDebounceTime_2 = currentMillis;
    buttonPressed_2 = true;
  }
}

void IRAM_ATTR buttonISR_3()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_3 > debounceDelay) 
  {
    lastDebounceTime_3 = currentMillis;
    buttonPressed_3 = true;
  }
}

void IRAM_ATTR buttonISR_4()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_4 > debounceDelay) 
  {
    lastDebounceTime_4 = currentMillis;
    buttonPressed_4 = true;
  }
}

#endif

