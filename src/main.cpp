#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Count_down.h"
#include "Button.h"
#include "HC_SR04.h"
#include "Var.h"  
#include "Blynk.h"    
#include "Cur_res.h"

void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);  // connect Blynk
  //setup_camera();

  pinMode(buzzer,OUTPUT);
  
  setup_sensor();
  setup_LCD();     
  setup_button();  // interrupt declaration
  setup_Cur_res();
  Ready();         // notice on LCD
}

void active_end()
{
  digitalWrite(relay, 1);  // off relay
  digitalWrite(buzzer,0);  // off buzzer
  stopCountdown();         // stop count down
  check_sensor = false;    // waiting flag indicates safe distance
  check_time_mode= false;  // waiting flag of each wait mode (adult, child mode 1: 30', child mode 2: 60', child mode 3: 90')
  State_bt = false;        // anti-jamming button status, Avoid pressing multiple buttons while in standby mode
  check_time_wait = false; // flag waiting for current
  flag_wait = false;       // current status flag
}

void handleButtonPress(float relayTime)
{
  if (!check_time_wait)                     // After the button is pressed:
  {        
    digitalWrite(relay, 0);  // on relay                        
    startMillis = millis();  // Start counting down the waiting time
    check_time_wait = true;     
    lcd.clear();
    lcd.print("Wait for the TV on");
  }

  if (check_time_wait && !check_time_mode)  //  + if there is current within 5s, the counter will start.
  {
    if(abs(mA) > 200)
    {
      flag_wait = true;
    }
    else if(millis() - startMillis >= 5000)  //  + if after 5s there is no current, the counter will stop and off relay
    {
      check_time_wait = false;
      digitalWrite(relay, 1);  // off relay 
      // lcd.clear();
      // lcd.print("End time wait");
      stop_noCur();
    }
  }

  if (flag_wait && !check_time_mode)     // Assign set time
  {
    check_time_mode = true;      
    startMillis = millis();   
    startCountdown(relayTime);  
  }

  if (check_time_mode)
  { 
    Check_distance();        // check the safe distance
    updateCountdown();       // countdown
  }
 
  if (check_time_mode && State_bt && (millis() - startMillis >= (relayTime * 60 * 1000) || abs(mA) < 200))  //When enough time has been counted or during the countdown process the current is lost
  {
    active_end();                                                                                          //  stop the countdown
  }
}

void Program()
{
  //-------------------------------------------
  if(buttonPressed[0])
  {
    handleButtonPress(0.1); //6s
    if (!check_time_wait)
    {
      buttonPressed[0] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[1])           //30 minite
  {
    handleButtonPress(0.2); //12s
    if (!check_time_wait)
    {
      buttonPressed[1] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[2])          //60 minite
  {
    handleButtonPress(0.4); //24s
    if (!check_time_wait)
    {
      buttonPressed[2] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[3])         //90 minite
  {
    handleButtonPress(0.6);  //36s
    if (!check_time_wait)
    {
      buttonPressed[3] = false;
    }
  }
  Blynk.run();
  Cacu_cur(); // Đọc cảm biến dòng
}
 
void loop()
{
  Program();
}