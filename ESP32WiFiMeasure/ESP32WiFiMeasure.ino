/*
 * sketch from here https://techtutorialsx.com/2017/06/29/esp32-arduino-getting-started-with-wifi/
 * ESP32 wifi scan 
 * 
 */


#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   23
#define OLED_CLK   18
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RESET 15
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
const int atas = 34;
const int bawah = 35;
const int kiri = 36;
const int kanan = 39;
bool flag = false;
const int n = 40;
String ssid[n];
String rssi[n];
String mac[n];
String enc[n];
int numberOfNetworks = 0;
int menu = 0;
String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}
 
//void scanNetworks() {
//  numberOfNetworks = WiFi.scanNetworks();
//  String ssid[numberOfNetworks];
//  String rssi[numberOfNetworks];
//  String mac[numberOfNetworks];
//  String enc[numberOfNetworks];
//  Serial.print("Number of networks found: ");
//  Serial.println(numberOfNetworks);
//  for (int i = 0; i < numberOfNetworks; i++) {
//    ssid[i] = WiFi.SSID(i);
//    rssi[i] = WiFi.RSSI(i);
//    mac[i] = WiFi.BSSIDstr(i);
//    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
//    enc[i] = encryptionTypeDescription;
// 
//  }
//}
 
void setup() {
 
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(500);
  display.clearDisplay();
  WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

  Serial.println("Setup done");
  delay(1000);
  pinMode(atas, INPUT);
  pinMode(bawah, INPUT);
  pinMode(kiri, INPUT);
  pinMode(kanan, INPUT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("click right button");
  display.println("first for scan");
  display.display();
}
 
void loop() 
{
  int left = digitalRead(kiri);
  int right = digitalRead(kanan);
  int up = digitalRead(atas);
  int down = digitalRead(bawah);

  if (right == HIGH)
  {
    if (flag == true)
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Scanning...");
      display.display();
      numberOfNetworks = WiFi.scanNetworks();
      delay(200);
      if (numberOfNetworks == 0)
      {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("no network found!");
        display.display();
      }
      else {
        for (int i = 0; i < numberOfNetworks; i++) {
          ssid[i] = WiFi.SSID(i);
          rssi[i] = WiFi.RSSI(i);
          mac[i] = WiFi.BSSIDstr(i);
          String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
          enc[i] = encryptionTypeDescription;
        }
        menu = 1;
      }
      flag = false;
    }
  }
  else if (right == LOW)
  {
    flag = true;
    if (numberOfNetworks == 0)
    {
      //do nothing
    }
    else
    {
      if (down == HIGH)
      {
        menu++;
      }
      else if (up == HIGH)
      {
        menu--;
      }
      if (menu > numberOfNetworks){
        menu = 1;
      }
      else if (menu <= 0){
        menu = numberOfNetworks;
      }  
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("SSID ");
      display.print(menu);
      display.print(" of ");
      display.println(numberOfNetworks);
      display.println(ssid[menu-1]);
      display.print(rssi[menu-1]);
      display.println(" dB");
      display.println(mac[menu-1]);
      display.println(enc[menu-1]);
      display.display();
    }
  }
  delay(210);
}
