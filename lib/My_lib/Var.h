#ifndef Var_H
#define Var_H

const char* ssid = "Home Unifi";
const char* password = "cotam123";

// WiFiUDP udp;
// NTPClient timeClient(udp, "pool.ntp.org", 25200, 3600); // Đồng bộ với máy chủ NTP, +0 giờ UTC

const uint8_t buttonPin_1 = 1; 
const uint8_t buttonPin_2 = 2; 
const uint8_t buttonPin_3 = 3; 
const uint8_t buttonPin_4 = 4; 

const int relay = 10;
const int bell = 9;

volatile bool buttonPressed_1 = false;
volatile bool buttonPressed_2 = false;
volatile bool buttonPressed_3 = false;
volatile bool buttonPressed_4 = false;

volatile unsigned long lastDebounceTime_1 = 0;
volatile unsigned long lastDebounceTime_2 = 0;
volatile unsigned long lastDebounceTime_3 = 0;
volatile unsigned long lastDebounceTime_4 = 0;
const unsigned long debounceDelay = 300; // Thời gian chờ để xử lý nhiễu (milliseconds)

uint8_t Set_time_day = 120 * 60 *1000;
bool ready = false;

#endif

