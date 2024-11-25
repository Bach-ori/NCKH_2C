#include <Arduino.h>
#include <WiFi.h>
//include <NTPClient.h>
#include <WiFiUdp.h>
#include "HC_SR04.h"
#include "Var.h"
#include "Button.h" 

void setup()
{
  Serial.begin(9600);     
  // Connect wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Lay real time
  //timeClient.begin();

  pinMode(relay,OUTPUT);
  setup_sensor();
  
  //interrupt
  pinMode(buttonPin_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_1), buttonISR_1, FALLING);

  pinMode(buttonPin_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_2), buttonISR_2, FALLING);

  pinMode(buttonPin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_3), buttonISR_3, FALLING);

  pinMode(buttonPin_4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_4), buttonISR_4, FALLING);
}

void Check_distance()
{
  sensor();
  static unsigned long safety_distance_time = millis();
  if (distance <= 1000 && (millis() - safety_distance_time >= 5000)) 
  {
    digitalWrite(bell,1);
  }
  else
  {
    safety_distance_time = millis();  
    digitalWrite(bell,0);
  }
}

void handleButtonPress(uint8_t relayTime)
{
  if(!check_time) 
  {
    startMillis = millis();
    check_time = true;;
  }

  digitalWrite(relay, 0);  //on relay
  Check_distance();        
  //send data & LCD

  if((millis() - startMillis >= (relayTime * 60 * 1000)) && check_time && State_bt) 
  {
    digitalWrite(relay, 1);  //off relay
    check_time = false;
    State_bt = false;
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
    handleButtonPress(30);
    if (!check_time)
    {
      buttonPressed[1] = false;
    }
  }
  else if(buttonPressed[2])            //60 minite
  {
    handleButtonPress(60);
    if (!check_time)
    {
      buttonPressed[2] = false;
    }
  }
  else if(buttonPressed[3])           //90 minite
  {
    handleButtonPress(90);
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
