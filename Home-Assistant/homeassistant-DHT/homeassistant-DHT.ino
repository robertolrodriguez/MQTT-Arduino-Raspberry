#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"       // DHT.h 라이브러리를 포함한다
#define DHTPIN 2      // DHT핀을 2번으로 정의한다(DATA핀)
#define DHTTYPE DHT11  // DHT타입을 DHT11로 정의한다
DHT dht(DHTPIN, DHTTYPE);  // DHT설정 - dht (디지털2, dht11)

// Update these with values suitable for your network.
char ssid[] = "xxxx";
char password[] = "xxxx";
int status = WL_IDLE_STATUS;
const char* mqtt_server = "xxx.xxx.x.x";  //server url
const char* topic = "mqtt/myroom";  //topic's name
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient client(mqtt_server, 1883, espClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.

  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  client.publish("mqtt/myroom", p, length);  // xxxx is your topic
  // Free the memory
  free(p);
}

//publish Message by json data type
//Because you want to send IOT data to 'Home-Assistant Service', 
//then ,you must change IOT data to json dat type.
void publishMessage()
{
  char message_room[50];
  String message = "{\"temp\":";
  message +=  dht.readTemperature();
  message +=  ", \"humi\":";
  message += dht.readHumidity();
  message += "}";
  
  message.toCharArray(message_room,message.length()+1);
  
  Serial.println(message_room);
  if (client.connect("arduinoClient"))
  {
    client.publish("mqtt/myroom", message_room);
  }
}


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  
 
}

void loop() 
{
  publishMessage();
  delay(9600);
}
