#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
const char* ssid     = "MES";
const char* password = "00000000";
IPAddress staticIP(172,16,3,80); // IP the board
IPAddress gateway(172,16,3,254);
IPAddress subnet(255,255,0,0);
 
void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin(ssid, password);   //WiFi connection
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
  }
  Serial.println("Connected..! :*");
}
 
void loop() {
 String LocalIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." +
   WiFi.localIP()[3];
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://172.16.1.7:80/MetalDetector/api/Sensor/Sensor");      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
   String httpRequestData = "device_ip=" + String(LocalIP) + "&device_mac=" + String(WiFi.macAddress())
                            + "&detect_id=2&date_time=2020/3/9 18:1:40&date_only=2020/3/9 ";
   Serial.println(httpRequestData);  
   int httpCode = http.POST(httpRequestData);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
    Serial.println("Error in WiFi connection");
 }
 delay(20000);  //Send a request every 30 seconds
}
