#include <Arduino.h>
#include <WiFi.h>
//include <NTPClient.h>
#include <WiFiUdp.h>
#include "HC_SR04.h"         
#include "Var.h"            
#include "Button.h"          
#include "ACS712.h"          
#include "Cur_res.h"
#include "Count_down.h"

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
  
  //Current
  setup_Cur_res();

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
  sensor_1();
  sensor_2();
  if(distance_1 <= 10 || distance_2 <= 10) 
  {
    if(!check_sensor)
    {
      safety_distance_time = millis();
      check_sensor = true;
    }
    if(check_sensor && (millis() - safety_distance_time >= 5000))
    {
      digitalWrite(buzzer,1);
    }
    delay(200);
  }
  else
  {
    check_sensor = false;
    digitalWrite(buzzer,0);
    Serial.println("Safe");
  }
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
  }

  Cacu_cur();
  if(mA <= abs(100))
  {
    digitalWrite(relay, 1);
    check_time = false;
    State_bt = false;
    stopCountdown();
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
