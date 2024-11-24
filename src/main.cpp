#include <Arduino.h>
#include <WiFi.h>
//include <NTPClient.h>
#include <WiFiUdp.h>
#include "HC_SR04.h"
#include "Var.h"
#include "Button.h" 

void setup()
{
  Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
  // Kết nối Wi-Fi
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
  

  //Khai bao ngat 
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

void Active()
{
  if(buttonPressed_1)  // adult
  {
    buttonPressed_1 = false;
  }
  else if(buttonPressed_2 && ready == false)  // kid 1
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 30 * 60 * 1000; // 30 phút
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1); // on relay
      Check_distance();
      ready = false;
      buttonPressed_2 = false;
      Serial.println("buttonPressed_2");
    }
  }
  else if(buttonPressed_3 && ready == false) // kid 3
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 60 * 60 * 1000; // 60 phút 
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1); // on relay
      Check_distance();
      ready = false;
      buttonPressed_3 = false;
      Serial.println("buttonPressed_3");
    }
  }
  else if(buttonPressed_4 && ready == false)  // kid 4
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 90 * 60 * 1000; // 90 phút
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1);  // on relay
      Check_distance();
      ready = false;
      buttonPressed_4 = false;
      Serial.println("buttonPressed_4");
    }
  }
}

void loop()
{
  Active();
}
