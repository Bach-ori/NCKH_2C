#ifndef Sensor_H
#define Sensor_H

const uint8_t trig_1 = 15;     
const uint8_t echo_1 = 7;     
const uint8_t trig_2 = 6;   
const uint8_t echo_2 = 5;     
const int buzzer = 4;
int distance_1 = 0;
int distance_2 = 0;
unsigned long safety_distance_time = 0;
bool check_sensor = false;               

void turnOnBuzzer()                   // Turn on relay
{
  digitalWrite(buzzer, HIGH);
}

void turnOffBuzzer()                  // Turn off relay
{
  digitalWrite(buzzer, LOW);
}

void setup_sensor()
{
  pinMode(trig_1,OUTPUT);   
  pinMode(echo_1,INPUT);    
  pinMode(trig_2,OUTPUT); 
  pinMode(echo_2,INPUT);   
}

void sensor_1()
{
  unsigned long duration;
    
  digitalWrite(trig_1,0);   
  delayMicroseconds(2);
  digitalWrite(trig_1,1);  
  delayMicroseconds(5);   
  digitalWrite(trig_1,0); 
  
  duration = pulseIn(echo_1,HIGH);  
  distance_1 = uint8_t(duration/2/29.412);
  
  //Serial.print(distance_1);
  //Serial.println("cm");
}

void sensor_2()
{
  unsigned long duration; 
      
  digitalWrite(trig_2,0); 
  delayMicroseconds(2);
  digitalWrite(trig_2,1);  
  delayMicroseconds(5);   
  digitalWrite(trig_2,0);  
  
  duration = pulseIn(echo_2,HIGH);  
  distance_2= uint8_t(duration/2/29.412);
  
  // Serial.print(distance_2);
  // Serial.println("cm");
}

void Check_distance()
{
  sensor_1();
  //sensor_2();
  if(distance_1 <= 10)// || distance_2 <= 10)    //If the distance is shorter than the safe distance, the horn will sound
  {
    Serial.println("Danger");
    if(!check_sensor)
    {
      safety_distance_time = millis();
      check_sensor = true;
    }
    if(check_sensor && (millis() - safety_distance_time >= 5000))
    {
      turnOnBuzzer();    
    }
  }
  else
  {
    check_sensor = false;
    turnOffBuzzer();
    Serial.println("Safe");
  }
}

#endif