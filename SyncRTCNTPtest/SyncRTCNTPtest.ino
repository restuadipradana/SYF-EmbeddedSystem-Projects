//ini hanya pseudocode, eh ngga deng

// LIBRARY
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "RTClib.h"
#include <NTPClient.h>
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
IPAddress staticIP(172,16,3,80); // IP the board
IPAddress gateway(172,16,3,254);
IPAddress subnet(255,255,0,0);
const int s = 2;//light status
const char *ssid     = "MES";
const char *password = "00000000";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "172.16.1.16", 25200);

void setup() {
  pinMode(s, OUTPUT); 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while(WiFi.status() != WL_CONNECTED) { 
    delay(250);
    digitalWrite(s, HIGH);
    delay(250);
    digitalWrite(s, LOW);
  }
  digitalWrite(s, HIGH);
  timeClient.begin();
  if (! rtc.begin()) {
    digitalWrite(s, LOW);
    while (1);
  }
  timeClient.update();
  unsigned long epoc = timeClient.getEpochTime();
  String formattedDate = timeClient.getFormattedDate();
  int yr = formattedDate.substring(0, 4).toInt();
  int mn = formattedDate.substring(5, 7).toInt();
  int dt = formattedDate.substring(8, 10).toInt();
  if (epoc > 200)
  {
    rtc.adjust(DateTime(yr, mn, dt, timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds()));
  }
}

void loop() {
  DateTime now = rtc.now();
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.println(timeClient.getFormattedDate());
  Serial.println(timeClient.getFormattedTime());
  Serial.println(timeClient.getEpochTime());
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println("-----------------------------");
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" - ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.println(now.unixtime());
  Serial.println("-----------------------------");

  delay(1000);

  
}
