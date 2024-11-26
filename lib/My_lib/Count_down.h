#ifndef Count_h
#define Count_h

#include <Arduino.h>

const unsigned long set_time_day = 120 * 60000; // Mốc thời gian cố định 120 phút (ms)
unsigned long countdownStartTime = 0;       // Thời gian bắt đầu đếm
unsigned long totalElapsedTime = 0;         // Tổng thời gian đã đếm được
unsigned long countdownDuration = 0;        // Thời gian đếm ngược hiện tại
bool isCountingDown = false;                // Cờ trạng thái đếm ngược
bool one_way = false;                       // Kiểm soát khởi tạo đếm ngược

void startCountdown(int minutes) 
{
  if (totalElapsedTime < set_time_day) 
  {
    countdownDuration = minutes * 60000; // Thời gian đếm ngược từ phút truyền vào
    countdownStartTime = millis();       // Lưu thời gian bắt đầu
    isCountingDown = true;               // Bật trạng thái đếm ngược
    Serial.print("Countdown started from ");
    Serial.print(minutes);
    Serial.println(" minutes.");
  } 
  else 
  {
    Serial.println("No time left to count!");
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

    Serial.print("Countdown stopped. Total elapsed time: ");
    Serial.print(totalElapsedTime / 60000);
    Serial.print(" minutes and ");
    Serial.print((totalElapsedTime % 60000) / 1000);
    Serial.println(" seconds.");

    unsigned long remainingTime = set_time_day - totalElapsedTime; // Tính thời gian còn lại
    Serial.print("Remaining time from fixed 120 minutes: ");
    Serial.print(remainingTime / 60000);
    Serial.print(" minutes and ");
    Serial.print((remainingTime % 60000) / 1000);
    Serial.println(" seconds.");
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
      Serial.print(remainingMinutes);
      Serial.print(":");
      if (remainingSeconds < 10) Serial.print("0");
      Serial.println(remainingSeconds);
    } 
    else 
    {
      Serial.println("Countdown finished!");
      totalElapsedTime += countdownDuration; // Cộng toàn bộ thời gian đếm vào tổng
      if (totalElapsedTime > set_time_day) totalElapsedTime = set_time_day; // Giới hạn tổng thời gian
      isCountingDown = false; // Dừng đếm ngược khi hết thời gian
    }
  }
}

void loop_test() 
{
  if (!one_way) 
  {
    startCountdown(30); // Bắt đầu đếm ngược 30 phút
    one_way = true;
  } 
  else if (one_way) 
  {
    updateCountdown(); // Cập nhật trạng thái đếm ngược
    delay(1000);       // Cập nhật mỗi giây
  }

  // Giả lập việc dừng sau 1 phút (60000ms)
  if (millis() > 60000 && isCountingDown) 
  {
    stopCountdown(); // Dừng đếm ngược
  }
}

#endif

