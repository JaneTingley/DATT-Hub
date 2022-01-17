/*this sketch is based off of this documentation; https://github.com/plapointe6/EspMQTTClient
 * */

#include "EspMQTTClient.h" // make sure this library is downloaded

EspMQTTClient client(
  "nameofNetwork", //SSID . "the name of your wifi Network"
  "password", //pssword . "password of your network"
  "datt2010-physical-computing.cloud.shiftr.io", // Location of Instance
  "physical2010computing", //Token Secret
  "ESP32-Hello-World", //ClientID
   1883  // port
);

unsigned long lastMillis = 0;
int crashCounter = 0;           // Variable holds count for how long connected to wifi

void setup(){
  Serial.begin(9600);
}

void onConnectionEstablished(){
  // do not delete
  client.subscribe("Light", onMessageReceived); // When the topic is received - call onMessageReceived function - which prints to serial
  client.subscribe("Wind", onMessageReceived); // subscribe here
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
