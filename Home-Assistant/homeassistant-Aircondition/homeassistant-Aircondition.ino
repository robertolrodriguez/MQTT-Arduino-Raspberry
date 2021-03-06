#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
char ssid[] = "xxxx";     //your wifi id
char password[] = "xxxx";     //your wifi password
int status = WL_IDLE_STATUS;
const char* mqtt_server = "xxx.xxx.xxx.xxx";   //server's url
const char* topic = "mqtt/Air_condition";                   //topic's name
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient client(mqtt_server, 1883, espClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {

  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  client.publish("mqtt/Air_condition", p, length);
  // Free the memory
  free(p);
}

void setup()
{
  Serial.begin(9600); //Set serial baud rate to 9600 bps
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

//publish Message by json data type
//Because you want to send IOT data to 'Home-Assistant Service', 
//then ,you must change IOT data to json dat type.
void publishMessage()
{  int val;
  char room_Aircondition[50];
  val=analogRead(0);//Read Gas value from analog 0
  String message = "{\"val\":";
  message += val;
  message += "}";
  
  message.toCharArray(room_Aircondition,message.length()+1);

  if(client.connect("arduinoClient"))
  {
    client.publish("mqtt/Air_condition", room_Aircondition);  //xxxx is your topic
  }
}

void loop()
{
 
  publishMessage();
 
 delay(9600);
}
