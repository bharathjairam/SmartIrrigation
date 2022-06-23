#include <ESP8266WiFi.h>
#include <Wire.h>

#include "Ubidots.h"

int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;
int moisture;




//WiFiClient client;

const char* UBIDOTS_TOKEN = "BBFF-duq0ujtiSOHQJ2Vw0rpAM6nadnG9Sz"; 
const char* ssid     = "MAJOR PROJECT"; // Your ssid
const char* password = "12345678"; // Your Password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() {
  Serial.begin(115200);
  delay(100);

 

  pinMode(D1,OUTPUT);
  pinMode(moisture, INPUT); // declare sensor as input
 

  
  
ubidots.wifiConnect(ssid, password);
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED) {
         delay(500);
         Serial.print(".");
         }
         
Serial.println("");
Serial.println("WiFi is connected");

}


void loop() { 

    moisture = irrigation_system();
    Serial.println();
    Serial.print("Mositure : ");
    Serial.print(output_value);
    Serial.println("%");
    
 
  ubidots.add("Mositure",output_value);
  ubidots.add("Motor",output_value);
  
  
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id
  if (bufferSent) {
   Serial.println("Values sent by the device");
  }
  delay(3000);
}

int irrigation_system(){
   output_value= analogRead(sensor_pin);
 output_value = map(output_value,550,10,0,100);
 
   if(output_value <0 ){
      digitalWrite(D1,HIGH);
     }
     else{
            digitalWrite(D1,LOW);
     }
   delay(1000);
   return output_value;
   
   }
