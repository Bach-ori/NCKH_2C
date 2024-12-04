#ifndef Blynk_H
#define Blynk_H

#define BLYNK_TEMPLATE_ID "TMPL6XMCsVVSS"
#define BLYNK_TEMPLATE_NAME "IoTc2"
#define BLYNK_AUTH_TOKEN "EtnFXvbVac0OqzTM2-FpIWwjdkzW2xG_"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "Button.h"

#define BT1 V0
#define BT2 V1
#define BT3 V2
#define BT4 V3

volatile bool Blynk_bt[4] = {false,false,false,false};
bool isAnyTrue = false;

BLYNK_WRITE(BT1)
{
  int p = param.asInt();
  if(p == 1)
  {
    buttonPressed[0] = true;
    State_bt = true;
  }
}

BLYNK_WRITE(BT2)
{
  int p = param.asInt();
  if(p == 1)
  {
    buttonPressed[1] = true;
    State_bt = true;
  }
}

BLYNK_WRITE(BT3)
{
  int p = param.asInt();
  if(p == 1)
  {
    buttonPressed[2] = true;
    State_bt = true;
  }
}

BLYNK_WRITE(BT4)
{
  int p = param.asInt();
  if(p == 1)
  {
    buttonPressed[3] = true;
    State_bt = true;
  }
}

#endif

