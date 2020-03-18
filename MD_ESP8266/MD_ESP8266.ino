#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("guest", "syf-origin");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
  }
}
 
void loop() {
 String LocalIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." +
   WiFi.localIP()[3];
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://172.16.165.79:49908/api/Sensor/Sensor");      //Specify request destination
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
 delay(15000);  //Send a request every 30 seconds
}
