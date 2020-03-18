// tutorial found at here https://randomnerdtutorials.com/esp32-esp8266-mysql-database-php/

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>


// Replace with your network credentials
const char* ssid     = "guest";
const char* password = "syf-origin";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://172.16.165.96:49908/api/Sensor/Sensor";
String sensorLocation = "SYF";
const int buttonPin = 35;     // the number of the pushbutton pin
const int ledPin =  2;      // the number of the LED pin
int buttonState = 0; 


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
      //String httpRequestData = "camera_ip=10.11.0.67&camera_mac=88:A9:A7:C0:00:30&group_id=0&group_name=ESP&name=ESP32&time_detect=1582740566020";

      String httpRequestData = String("detect_id=") + String("1") + String("&device_ip=") + String(WiFi.localIP())
                            + String("&device_mac=") + String(WiFi.macAddress()) + String("&loc=") + String(sensorLocation) + String("");
      
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
          
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    //Send an HTTP POST request every 30 seconds
    delay(500); 
  } 
}

/*
 * 
 *    // Prepare your HTTP POST request data
      //String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
      //                      + "&location=" + sensorLocation + "&value1=" + String(bme.readTemperature())
      //                      + "&value2=" + String(bme.readHumidity()) + "&value3=" + String(bme.readPressure()/100.0F) + "";
      
      
      // You can comment the httpRequestData variable above
      // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";
      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
       
 * 
 */
