#ifndef Count_h
#define Count_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Khởi tạo LCD (địa chỉ 0x27, kích thước 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned long set_time_day = 120 * 60000; // Mốc thời gian cố định 120 phút (ms)
unsigned long countdownStartTime = 0;       // Thời gian bắt đầu đếm
unsigned long totalElapsedTime = 0;         // Tổng thời gian đã đếm được
unsigned long countdownDuration = 0;        // Thời gian đếm ngược hiện tại
bool isCountingDown = false;                // Cờ trạng thái đếm ngược
String mode = "";

void startCountdown(float minutes) 
{
  if (totalElapsedTime < set_time_day) 
  {
    countdownDuration = minutes * 60000; // Thời gian đếm ngược từ phút truyền vào
    countdownStartTime = millis();       // Lưu thời gian bắt đầu
    isCountingDown = true;               // Bật trạng thái đếm ngược
    
    if(minutes == 30 || minutes == 0.5)
    {
      mode = "Child mode 1";
    }
    else if(minutes == 60 || minutes == 0.7)
    {
      mode = "Child mode 2";
    }
    else if(minutes == 90 || minutes == 1)
    {
      mode = "Child mode 3";
    }
    else
    {
      mode = "Adult mode";
    }

    lcd.clear();
    lcd.print(mode);
  } 
  else 
  {    
    lcd.clear();
    lcd.print("No time left!");
  }
}

void stopCountdown() 
{
  if (isCountingDown) 
  {
    unsigned long elapsedTime = millis() - countdownStartTime; // Thời gian đếm hiện tại
    totalElapsedTime += elapsedTime;                           // Cộng vào tổng thời gian đã đếm
    if (totalElapsedTime > set_time_day) totalElapsedTime = set_time_day; // Giới hạn không vượt quá 120 phút

    isCountingDown = false; // Dừng đếm ngược

    unsigned long remainingTime = set_time_day - totalElapsedTime; // Tính thời gian còn lại

    lcd.clear();
    lcd.print("Elapsed: ");
    lcd.setCursor(9, 0);
    lcd.print(totalElapsedTime / 60000);
    lcd.print("'");
    lcd.print((totalElapsedTime % 60000) / 1000);
    lcd.print("s");

    lcd.setCursor(0, 1);
    lcd.print("Remain: ");
    lcd.print(remainingTime / 60000);
    lcd.print("'");
    lcd.print((remainingTime % 60000) / 1000);
    lcd.print("s");
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

      // Hiển thị thời gian còn lại
      lcd.setCursor(0, 1);
      lcd.print("C_time: ");
      lcd.print(remainingMinutes);
      lcd.print(":");
      if (remainingSeconds < 10) lcd.print("0");
      lcd.print(remainingSeconds);
    } 
    else 
    {
      lcd.print("Countdown done!");
      totalElapsedTime += countdownDuration; // Cộng toàn bộ thời gian đếm vào tổng
      if (totalElapsedTime > set_time_day) totalElapsedTime = set_time_day; // Giới hạn tổng thời gian
      isCountingDown = false; // Dừng đếm ngược khi hết thời gian
    }
  }
}

void setup_LCD() 
{
  lcd.init();          // Khởi tạo LCD
  lcd.backlight();     // Bật đèn nền
}


#endif