#include <Arduino.h>
#include <WiFi.h>
//include <NTPClient.h>
#include <WiFiUdp.h>
#include "HC_SR04.h"

const char* ssid = "Home Unifi";
const char* password = "cotam123";

const int buttonPin_1 = 1; 
const int buttonPin_2 = 2; 
const int buttonPin_3 = 3; 
const int buttonPin_4 = 4; 

const int relay = 10;
const int bell = 9;

volatile bool buttonPressed_1 = false;
volatile bool buttonPressed_2 = false;
volatile bool buttonPressed_3 = false;
volatile bool buttonPressed_4 = false;

volatile unsigned long lastDebounceTime_1 = 0;
volatile unsigned long lastDebounceTime_2 = 0;
volatile unsigned long lastDebounceTime_3 = 0;
volatile unsigned long lastDebounceTime_4 = 0;
const unsigned long debounceDelay = 300; // Thời gian chờ để xử lý nhiễu (milliseconds)

  // Time
int timezone = 7 * 3600; // GMT+7
int dst = 0;

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

void setup()
{
  // Kết nối Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  // Bắt đầu NTP client
  //timeClient.begin();

  pinMode(relay,OUTPUT);
  setup_sensor();
  

  pinMode(buttonPin_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_1), buttonISR_1, FALLING);

  pinMode(buttonPin_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_2), buttonISR_2, FALLING);

  pinMode(buttonPin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_3), buttonISR_3, FALLING);

  pinMode(buttonPin_4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin_4), buttonISR_4, FALLING);
}

int Set_time_day = 120;
bool ready = false;

void Check_distance()
{
  sensor();
  int safety_distance_time = millis();
  if (distance <= 1000 && (millis() - safety_distance_time >= 5000)) 
  {
    digitalWrite(bell,1);
  }
  else
  {
    digitalWrite(bell,0);
  }
}

void loop()
{
  if(buttonPressed_1)  // adult
  {
    buttonPressed_1 = false;
  }
  else if(buttonPressed_2 && ready == false)  // kid 1
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 1800;
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1); // on relay
      Check_distance();
      ready = false;
      buttonPressed_2 = false;
    }
  }
  else if(buttonPressed_3 && ready == false) // kid 3
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 3600;
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1); // on relay
      Check_distance();
      ready = false;
      buttonPressed_3 = false;
    }
  }
  else if(buttonPressed_4 && ready == false)  // kid 4
  {
    ready = true;
    digitalWrite(relay,0);
    int Wait_time = 5400;
    unsigned long ht = millis();
    if(ht - millis() >= Wait_time)
    {
      //send data
      //LCD
      digitalWrite(relay,1);  // on relay
      Check_distance();
      ready = false;
      buttonPressed_4 = false;
    }
  }
}
