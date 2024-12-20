#ifndef Cur_res_h
#define Cur_res_h

#include "ACS712.h"
ACS712 sensor(ACS712_05B, 14);

float I;
float I_TB;
float tong;
float mA;
int zero;
bool again = false;
unsigned long startMillis_cur;

void setup_Cur_res() 
{
  delay(200);
  zero = sensor.calibrate();
}

void Cacu_cur() 
{
  if(!again)
  {
    startMillis_cur = millis();
    again = true;
  }
  tong = 0;
  if(again && (millis() - startMillis_cur > 500))
  {
    tong = 0;
    for(int i=0;i<100;i++)
    {
      I = sensor.getCurrentDC();
      tong = tong + I;
    }
    I_TB = tong/100;
    mA = I_TB * 1000;
    Serial.println(abs(mA));
    again = false;
  }
}

#endif
