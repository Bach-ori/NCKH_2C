#ifndef Var_H
#define Var_H

//IO relay
const int relay = 19;
const int Cur = 14;

unsigned long startMillis;

// Thông tin WiFi
const char* ssid = "Home Unifi";
const char* password = "cotam123";

// Thông tin NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); // GMT+7 (giờ Việt Nam)

//check current
bool check_time_wait = false;
bool flag_wait = false;      

bool state_bt_1 = false;

#endif