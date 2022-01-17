/*this sketch is based off of this documentation; https://github.com/plapointe6/EspMQTTClient
 * */

#include "EspMQTTClient.h" // make sure this library is downloaded

EspMQTTClient client(
  "SSID", //SSID . "the name of your wifi Network"
  "Password", //pssword . "password of your network"
  "nameOfInstance.cloud.shiftr.io", // Location of Instance
  "nameOfInstance", //Name of Instance
  "TokenSecret", //Token Secret
  "ESP32-Hello-World", //ClientID
   1883  // port
);

unsigned long lastMillis = 0;
int crashCounter = 0;           // Variable holds count for how long connected to wifi

void setup(){
  Serial.begin(9600);
}

void onConnectionEstablished(){
  client.subscribe("Topic", onMessageReceived); // When the topic is received - call onMessageReceived function - which prints to serial
   //client.subscribe("#", onMessageReceived); // subscribe to all
}

void loop(){
  client.loop();
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    client.publish("ESP32-HelloWorld", String(crashCounter)); // publishing a count
    crashCounter++;
  }  
}

void onMessageReceived(const String& topic, const String& message) {
  Serial.println(topic + ": " + message);
}
