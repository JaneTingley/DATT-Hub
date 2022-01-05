// This example uses an Arduino Uno together with
// an Ethernet Shield to connect to shiftr.io.
// It also automatically asks for an IP address. This code was taken from
// EXAMPLES/Ethernet/DhcpAddressPrinter
//
// You can see the information here"

// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <Ethernet.h>
//#include <Dhcp.h>
#include <MQTT.h>
#include <SPI.h> //from DhcpAddressPrinter

    // from DhcpAddressPrinter 
                byte mac[] = {
                  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x11 /*change mac address everytime - so it is different from other MAC addresses
                  on send arduino */
                };
    // end from DhcpAddressPrinter

EthernetClient net;
MQTTClient client;
int variableName;
int topicOfChoiceVaiable;


void setup() {
  Serial.begin(9600); 
// from DhcpAddressPrinter 
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
// end from DhcpAddressPrinter
    
  client.begin("public.cloud.shiftr.io", net);
  client.onMessage(messageReceived); // call this function (message received) whenever there is a message

  connect();
}

void loop() {

  client.loop();
  
  if (!client.connected()) {
      connect();
  } 
      

  // from DhcpAddressPrinter 
    switch (Ethernet.maintain()) {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      break;
      
  }
  // end from DhcpAddressPrinter

}

void connect() { // connects to Shiftr
  Serial.print("connecting...");

  while (!client.connect("ClientID", "nameOfInstance", "TokenSecret")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!"); //  '/n' means start at new line
  
// subscribe to all of the topics
  client.subscribe("/TopicOfChoice"); //     '/' all names start with a slash
 
}


void publishValues() {  // This is it's own function - you can call it when you need it - or just put the below code where you need it.

  client.publish("/Topic/Name", String(variableName));  // Publish to Shiftr
  Serial.print("variableName : ");
  Serial.println(variableName);


}
    
void messageReceived(String &topic, String &payload) {   // string is a type of variable - a series of characters (topic= /WetSoil  payload= the value

  if (topic == "/TopicOfChoice"){
   topicOfChoiceVaiable = payload.toInt();;  // this stores Light into 1st position of array
  }
  
  Serial.print("TopicOfChoice: " );  
  Serial.println(topicOfChoiceVaiable);

  //or: Serial.println("incoming: " + topic + " - " + payload);  // To print all values to Serial

  
}
