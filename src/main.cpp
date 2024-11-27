#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Count_down.h"
#include "Button.h"
#include "HC_SR04.h"
#include "Var.h"    

void setup()
{
  Serial.begin(115200);

  // Kết nối WiFi
  Serial.print("Đang kết nối WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi!");
  timeClient.begin();

  pinMode(buzzer,OUTPUT);
  
  setup_sensor();
  setup_LCD();
  setup_button();
}

void handleButtonPress(uint8_t relayTime)
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
    stopCountdown();
    check_time = false;
    State_bt = false;
    lcd.clear();
  }
}

void Program()
{
  if(buttonPressed[0])
  {
    buttonPressed[0] = false;
  }
  else if(buttonPressed[1])            //30 minite
  {
    handleButtonPress(1);
    if (!check_time)
    {
      buttonPressed[1] = false;
    }
  }
  else if(buttonPressed[2])            //60 minite
  {
    handleButtonPress(1);
    if (!check_time)
    {
      buttonPressed[2] = false;
    }
  }
  else if(buttonPressed[3])           //90 minite
  {
    handleButtonPress(2);
    if (!check_time)
    {
      buttonPressed[3] = false;
    }
  }
}
 
void loop()
{
  Program();
}