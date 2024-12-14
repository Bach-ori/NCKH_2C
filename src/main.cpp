#include <Arduino.h>
#include "Var.h"

void handleButtonPress(float relayTime)
{
  if (!check_time_wait)      // After the button is pressed:
  {        
    turnOnRelay();  // on relay                        
    startMillis = millis();  // Start counting down the waiting time
    check_time_wait = true;     
    lcd.clear();
    lcd.print("Wait for the TV on");
  }

  if (check_time_wait && !check_time_mode)  
  {
    if(abs(mA) > threshold_cur)                        //  + if there is current within 5s, the counter will start.
    {
      flag_wait = true;
    }
    else if(millis() - startMillis >= 5000)  //  + if after 5s there is no current, the counter will stop and off relay
    {
      check_time_wait = false;
      turnOffRelay();   // off relay 
      stop_noCur();
    }
  }

  if (flag_wait && !check_time_mode)     // Assign set time
  {
    check_time_mode = true;      
    startMillis = millis();   
    startCountdown(relayTime);  
  }

  if (check_time_mode)
  { 
    Check_distance();        // check the safe distance
    updateCountdown();       // countdown
    if (check_time_mode && State_bt && (millis() - startMillis >= (relayTime * 60 * 1000) || abs(mA) < threshold_cur))  //When enough time has been counted or during the countdown process the current is lost
    {
      active_end();                                                                                          //  stop the countdown
      flag_end();
    }
  }
}

void Program()
{
  //-------------------------------------------
  if(buttonPressed[0])
  {
    toggleRelay();
  }
  //-------------------------------------------
  for (int i = 0; i < 3; i++) 
  {
    if (buttonPressed[i + 1]) 
    {
        handleButtonPress(relayTimes[i]);
        if (!check_time_wait) 
        {
          buttonPressed[i + 1] = false;
        }
    }
  }
  Blynk.run(); 
  Cacu_cur();   //Caculator current
}
 
void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);  // connect Blynk

  pinMode(buzzer,OUTPUT); 
  pinMode(relay,OUTPUT);

  setup_sensor();
  setup_LCD();     
  setup_button();  // interrupt declaration
  setup_Cur_res();
  Ready();         // notice on LCD
}

void loop()
{
  Program();
}

