#ifndef Var_H
#define Var_H

#include <Arduino.h>
#include "Var.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Count_down.h"
#include "Blynk.h"  
#include "Button.h"
#include "HC_SR04.h"     
#include "Cur_res.h"

//IO relay
const int relay = 19;
const int Cur = 14;

unsigned long startMillis;

// Thông tin WiFi
const char* ssid = "Home Unifi";
const char* password = "cotam123";

// Thông tin NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); // GMT+7 (giờ Việt Nam)

//check current
bool check_time_wait = false;
bool flag_wait = false;      

// current threshold
const uint16_t threshold_cur = 2000;

//Set time mode
const float relayTimes[] = {0.2, 0.4, 0.6}; // 30, 60, 90 minutes

//funtion code 
void check_time_day()                 //After 00:00 every day, set the TV viewing time to 0
{
  timeClient.update(); 

  int8_t hours = timeClient.getHours();
  int8_t minutes = timeClient.getMinutes();
  int8_t seconds = timeClient.getSeconds();

  if (hours == 0 && minutes == 0 && seconds == 0) 
  {
    totalElapsedTime = 0; 
  }
}

void turnOnRelay()                    // Turn on relay
{
  digitalWrite(relay, HIGH);
}

void turnOffRelay()                  // Turn off relay
{
  digitalWrite(relay, LOW);
}
 
void toggleRelay()                   // Reverse the relay on/off status when in adult mode
{
  lcd.clear();
  if (digitalRead(relay) == HIGH) 
  {
    turnOffRelay();
    Blynk.virtualWrite(V5,"No mode is selected");
    lcd.clear();
  } 
  else 
  {
    turnOnRelay();
    Blynk.virtualWrite(V5,"Adult Mode");
    lcd.print("Adult mode");
  }
  buttonPressed[0] = false;
  State_bt = false;
}

void active_end()                     // End operations after the mode ends
{
  turnOffRelay() ;  // off relay
  turnOffBuzzer();  // off buzzer
  stopCountdown();  // stop count down
}

void flag_end()                       // Returns the flag to its original state
{
  check_sensor = false;    // waiting flag indicates safe distance
  check_time_mode= false;  // waiting flag of each wait mode (adult, child mode 1: 30', child mode 2: 60', child mode 3: 90')
  State_bt = false;        // anti-jamming button status, Avoid pressing multiple buttons while in standby mode
  check_time_wait = false; // flag waiting for current
  flag_wait = false;       // current status flag
}

#endif
