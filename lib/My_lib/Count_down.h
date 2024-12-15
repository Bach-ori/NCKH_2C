#ifndef Count_h
#define Count_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Blynk.h"
#include "Var.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned long set_time_day = 2 * 60000; // Fixed time point 120 minutes (ms)
unsigned long countdownStartTime = 0;         // Time begins to count
unsigned long totalElapsedTime = 0;           // Total time counted
unsigned long countdownDuration = 0;          // Current countdown time
bool isCountingDown = false;                  // Countdown status flag
String mode = "";

void Ready()
{
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("READY");
  delay(2000);
  lcd.clear();
}

void startCountdown(float minutes) 
{
  if (totalElapsedTime < set_time_day) 
  {
    countdownDuration = minutes * 60000; // The time counts down from the minute of infusion
    countdownStartTime = millis();       // Save start time
    isCountingDown = true;               // Turn on countdown status
    
    if (fabs(minutes - 0.2) < 0.01)        // 30 minutes
    {
      mode = "Child mode 1";
    }
    else if (fabs(minutes - 0.4) < 0.01)       // 60 minutes
    {
      mode = "Child mode 2";
    }
    else if (fabs(minutes - 0.6) < 0.01) // 90 minutes
    {
      mode = "Child mode 3";
    }

    lcd.clear();
    lcd.print(mode);
  } 
  else 
  {    
    countdownDuration = minutes * 60000; 
    countdownStartTime = millis();    
    isCountingDown = true;            
    
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Time max");
    //notice
  }
}

void stopCountdown() 
{
  if (isCountingDown) 
  {
    unsigned long elapsedTime = millis() - countdownStartTime;
    totalElapsedTime += elapsedTime;                          

    isCountingDown = false; 

    unsigned long remainingTime = set_time_day - totalElapsedTime; 

    if(remainingTime <= 0)
    {
      remainingTime = 0;
    }
    Blynk.virtualWrite(V4,totalElapsedTime/60000);  

    lcd.clear();
    lcd.print("Elapsed: ");
    lcd.setCursor(9, 0);
    lcd.print(totalElapsedTime / 60000);
    lcd.print("'");
    lcd.print((totalElapsedTime % 60000) / 1000);
    lcd.print("s");
    Blynk.virtualWrite(V5,"No mode is selected");

    if (totalElapsedTime <= set_time_day)
    {
      lcd.setCursor(0, 1);
      lcd.print("Remain: ");
      lcd.print(remainingTime / 60000);
      lcd.print("'");
      lcd.print((remainingTime % 60000) / 1000);
      lcd.print("s");
    }
    else
    {
      lcd.setCursor(3, 1);
      lcd.print("Time max");
    }
  }
}

void updateCountdown() 
{
  if (isCountingDown) 
  {
    unsigned long elapsedTime = millis() - countdownStartTime;
    unsigned long currentRemainingTime = countdownDuration - elapsedTime;

    if (currentRemainingTime > 0) 
    {
      int remainingMinutes = currentRemainingTime / 60000;
      int remainingSeconds = (currentRemainingTime % 60000) / 1000;

      lcd.setCursor(0, 1);
      lcd.print("C_time: ");
      lcd.print(remainingMinutes);
      lcd.print(":");
      if (remainingSeconds < 10) lcd.print("0");
      lcd.print(remainingSeconds);
    } 
    else 
    {
      totalElapsedTime += countdownDuration; // Add all the counting times to the total
      isCountingDown = false;                // Stop countdown when time runs out
    }
  }
}

void stop_noCur()   // When the 5s waiting time has passed
{
  unsigned long remainingTime = set_time_day - totalElapsedTime; 

  if(remainingTime <= 0)
  {
    remainingTime = 0;
  }
  Blynk.virtualWrite(V4,totalElapsedTime/60000);  

  lcd.clear();
  lcd.print("Elapsed: ");
  lcd.setCursor(9, 0);
  lcd.print(totalElapsedTime / 60000);
  lcd.print("'");
  lcd.print((totalElapsedTime % 60000) / 1000);
  lcd.print("s");
  Blynk.virtualWrite(V5,"No mode is selected");

  if (totalElapsedTime <= set_time_day)
  {
    lcd.setCursor(0, 1);
    lcd.print("Remain: ");
    lcd.print(remainingTime / 60000);
    lcd.print("'");
    lcd.print((remainingTime % 60000) / 1000);
    lcd.print("s");
  }
  else
  {
    lcd.setCursor(3, 1);
    lcd.print("Time max");
  }
}

void setup_LCD() 
{
  lcd.init();          // Khởi tạo LCD
  lcd.backlight();     // Bật đèn nền
}


#endif