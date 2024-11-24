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
volatile bool buttonPressed_1 = false; 
volatile bool buttonPressed_2 = false;
volatile bool buttonPressed_3 = false;
volatile bool buttonPressed_4 = false;

volatile unsigned long lastDebounceTime_1 = 0;
volatile unsigned long lastDebounceTime_2 = 0;
volatile unsigned long lastDebounceTime_3 = 0;
volatile unsigned long lastDebounceTime_4 = 0;
const unsigned long debounceDelay = 300; // Thời gian chờ để xử lý nhiễu (milliseconds)
uint8_t check_button_loop = 0;  // Tránh nhấn nhiều lần 1 nút

unsigned long Set_time_day = 120 * 60 * 1000;
bool check_time = false;
unsigned long startMillis;

bool Bt_ready_1 = false;
bool Bt_ready_2 = false;
bool Bt_ready_3 = false;
bool Bt_ready_4 = false;

bool* Bt_ready[] = {&Bt_ready_1, &Bt_ready_2, &Bt_ready_3, &Bt_ready_4};

void setBtReady(int index) 
{
  for (int i = 0; i < 4; i++) 
  {
    *Bt_ready[i] = (i != index - 1); // Đặt true nếu không trùng index
  }
}

void resetBtReady() 
{
  for (int i = 0; i < 4; i++) 
  {
    *Bt_ready[i] = false;  // Đặt giá trị của từng biến trỏ tới bằng false
  }
}

void IRAM_ATTR buttonISR_1()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_1 > debounceDelay) 
  {
    lastDebounceTime_1 = currentMillis;
    buttonPressed_1 = true;
    check_button_loop++;
  }
}

void IRAM_ATTR buttonISR_2()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_2 > debounceDelay) 
  {
    lastDebounceTime_2 = currentMillis;
    buttonPressed_2 = true;
    check_button_loop++;
  }
}

void IRAM_ATTR buttonISR_3()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_3 > debounceDelay) 
  {
    lastDebounceTime_3 = currentMillis;
    buttonPressed_3 = true;
    check_button_loop++;
  }
}

void IRAM_ATTR buttonISR_4()   //chuyển chế độ 
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime_4 > debounceDelay) 
  {
    lastDebounceTime_4 = currentMillis;
    buttonPressed_4 = true;
    check_button_loop++;
  }
}

#endif

