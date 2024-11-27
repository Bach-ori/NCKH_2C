#ifndef Var_H
#define Var_H

//IO relay
const int relay = 14;

unsigned long startMillis;

// Thông tin WiFi
const char* ssid = "Home Unifi";
const char* password = "cotam123";

// Thông tin NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); // GMT+7 (giờ Việt Nam)

#endif
