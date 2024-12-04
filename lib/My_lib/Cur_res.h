#ifndef Cur_res_h
#define Cur_res_h

#include "ACS712.h"
#include "HC_SR04.h"
#include "Button.h"
ACS712 sensor(ACS712_05B, 14);

float I;
float I_TB;
float tong;
float mA;

void setup_Cur_res() 
{
  int zero = sensor.calibrate();
  delay(3000);
}

void Cacu_cur() 
{
  for(int i=0;i<100;i++)
  {
    float I = sensor.getCurrentDC();
    tong = tong + I;
  }
  I_TB = tong/100;
  tong = 0;
  mA = I_TB * 1000;
  Serial.println(abs(mA));
}

#endif
