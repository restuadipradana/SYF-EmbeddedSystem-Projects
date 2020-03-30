#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0xF6, 0xFF }; 
byte ip[] = {  172, 16, 3, 80};
byte gateway[] = { 172, 16, 3, 254 };           

EthernetClient client;


void setup()
{
Ethernet.begin(mac, ip, gateway);
Serial.begin(115200 );
Serial.println(Ethernet.localIP());
delay(1000);
Serial.println("connecting...");


}

void loop()                                           
{   
String httpRequestData = "device_ip=172.16.3.80&device_mac=90:A2:DA:0D:F6:FF&detect_id=2&date_time=2020/3/9 18:1:40&date_only=2020/3/9 ";
if (client.connect("172.16.1.7",80))
{                                 
Serial.println("Sending to Server: ");                    
client.println("POST http://172.16.1.7:80/MetalDetector/api/Sensor/Sensor HTTP/1.1");           
Serial.print("POST http://172.16.1.7:80/MetalDetector/api/Sensor/Sensor HTTP/1.1");           
client.println("Host: 172.16.1.7");
client.println("Content-Type: application/x-www-form-urlencoded");
client.println("Connection: close");
client.print("Content-Length: ");
client.println(httpRequestData.length());
client.println();
client.print(httpRequestData);
client.println();                                           
}
else
{
Serial.println("Cannot connect to Server");               
} 

    
if (client.available()) {
char c = client.read();
Serial.print(c);
}
if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

  
}


delay(10000);

}
