#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Var.h"
const uint8_t trig_1 = 15;     
const uint8_t echo_1 = 7;     
const uint8_t trig_2 = 6;     
const uint8_t echo_2 = 5;     
int distance_1 = 0;
int distance_2 = 0;
unsigned long safety_distance_time = 0;
bool check_sensor = false;

void setup_sensor()
{
    pinMode(trig_1,OUTPUT);   // chân trig_1 sẽ phát tín hiệu
    pinMode(echo_1,INPUT);    // chân echo_1 sẽ nhận tín hiệu

    pinMode(trig_2,OUTPUT);   
    pinMode(echo_2,INPUT); 
}
 
void sensor_1()
{
    unsigned long duration; // biến đo thời gian
        
    /* Phát xung từ chân trig_1 */
    digitalWrite(trig_1,0);   // tắt chân trig_1
    delayMicroseconds(2);
    digitalWrite(trig_1,1);   // phát xung từ chân trig_1
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig_1,0);   // tắt chân trig_1
    
    duration = pulseIn(echo_1,HIGH);  
    distance_1 = uint8_t(duration/2/29.412);
}

void sensor_2()
{
    unsigned long duration; // biến đo thời gian
        
    /* Phát xung từ chân trig_1 */
    digitalWrite(trig_2,0);   // tắt chân trig_1
    delayMicroseconds(2);
    digitalWrite(trig_2,1);   // phát xung từ chân trig_1
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig_2,0);   // tắt chân trig_1
    
    duration = pulseIn(echo_2,HIGH);  
    distance_2 = uint8_t(duration/2/29.412);
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
  }
  else
  {
    check_sensor = false;
    digitalWrite(buzzer,0);
    Serial.println("Safe");
  }
}

#endif

