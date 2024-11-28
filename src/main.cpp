#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Count_down.h"
#include "Button.h"
#include "HC_SR04.h"
#include "Var.h"  
#include "Blynk.h"    

void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  pinMode(buzzer,OUTPUT);
  
  setup_sensor();
  setup_LCD();
  setup_button();
  Ready();
}

void handleButtonPress(float relayTime)
{
  if(!check_time) 
  {
    startMillis = millis();
    startCountdown(relayTime);
    check_time = true;
  }
  
  digitalWrite(relay, 0);  //on relay
  Check_distance();       
  updateCountdown(); //LCD
  //send data

  if((millis() - startMillis >= (relayTime * 60 * 1000)) && check_time && State_bt) 
  {
    digitalWrite(relay, 1);  //off relay
    digitalWrite(buzzer,0);  // off buzzer
    stopCountdown();
    check_time = false;
    State_bt = false;
    lcd.clear();
  }

}

void Program()
{
  //-------------------------------------------
  if(buttonPressed[0])
  {
    handleButtonPress(0.1); //6s
    if (!check_time)
    {
      buttonPressed[0] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[1])           //30 minite
  {
    handleButtonPress(0.2); //12s
    if (!check_time)
    {
      buttonPressed[1] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[2])          //60 minite
  {
    handleButtonPress(0.4); //24s
    if (!check_time)
    {
      buttonPressed[2] = false;
    }
  }
  //-------------------------------------------
  else if(buttonPressed[3])         //90 minite
  {
    handleButtonPress(0.6);  //36s
    if (!check_time)
    {
      buttonPressed[3] = false;
    }
  }
  Blynk.run();
}
 
void loop()
{
  Program();
}