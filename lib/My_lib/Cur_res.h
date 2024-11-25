#ifndef Cur_res_h
#define Cur_res_h

#include "ACS712.h"
ACS712 sensor(ACS712_05B, A0);

float I;
float I_TB;
float tong;
float ma;

void setup_Cur_res() 
{
  int zero = sensor.calibrate();
}

void Cacu_cur() 
{
  digitalWrite(2,0);

  for(int i=0;i<100;i++)
  {
    float I = sensor.getCurrentDC();
    tong = tong + I;
  }
  I_TB = tong/100;
  tong = 0;
  ma = I_TB * 1000;
}

#endif
