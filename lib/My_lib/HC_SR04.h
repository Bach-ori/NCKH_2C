#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
const uint8_t trig = 8;     // chân trig của HC-SR04
const uint8_t echo = 7;     // chân echo của HC-SR04
int distance = 0;
unsigned long safety_distance_time = 0;
bool check_sensor = false;
 
void setup_sensor()
{
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
}
 
void sensor()
{
    unsigned long duration; // biến đo thời gian
        
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = uint8_t(duration/2/29.412);
    
    // /* In kết quả ra Serial Monitor */
    // Serial.print(distance);
    // Serial.println("cm");
    // delay(200);
}

#endif

