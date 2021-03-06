#include <Wire.h> 
#include <SparkFunMLX90614.h> 
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
char ssid[] = "wifi ID";     //your wifi id
char password[] = "wifi Password";     //your wifi password
int status = WL_IDLE_STATUS;
const char* mqtt_server = "xxx.xxx.xxx.xxx";   //server's url
const char* topic = "your topic's name";                   //topic's name
IRTherm therm; 
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
  client.publish("your topic's name", p, length); //xxxx is your topic
  // Free the memory
  free(p);
}

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output
  
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
    
    delay(9600);
 }
 
  Serial.print("You're connected to the network");
  
  therm.begin(); // Initialize thermal IR sensor
  therm.setUnit(TEMP_C); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
}

void loop() 
{
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
	// temperatures.
	// They'll be floats, calculated out to the unit you set with setUnit().
    char Object[6];
    char Ambient[6];

    char kitchen[34];
    
    dtostrf(therm.object(), 2, 2, Object);
    dtostrf(therm.ambient(), 2 ,2, Ambient);
 
    sprintf(kitchen, "Cooker: %sC Ambient: %sC", Object, Ambient);
    
   if(client.connect("arduinoClient"))
   {
     client.publish("your topic's name",kitchen); //xxxx is your topic
   }
   
}
 
  delay(9600);
}
