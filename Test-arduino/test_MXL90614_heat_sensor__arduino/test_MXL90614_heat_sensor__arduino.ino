#include <Wire.h> 
#include <SparkFunMLX90614.h> 

IRTherm therm; 

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output
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
    
    Serial.println(kitchen);
}
 
  delay(9600);
}
