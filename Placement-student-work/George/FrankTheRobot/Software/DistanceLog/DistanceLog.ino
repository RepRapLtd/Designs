/*
  Getting distance from the RFD77402 Time of Flight Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: June 6th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!

  Read the raw distance values from the vertical-cavity surface-emitting laser (VCSEL) sensor.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield (any port)
  Open the serial monitor at 9600 baud
*/

/*
 * Modified to display a scrolling graph of distances in the Arduino Serial Monitor.
 * 
 * Adrian Bowyer
 * RepRap Ltd
 * https://reprapltd.com
 * 
 * 17/11/2017
 * 
 * CAUTION!!! Only use a 3V3 Arduino like the Due or the Wemos D1 (which is not an actual Arduino, but you know what I mean).
 * A 5V Arduino will damage the RFD77402.
 * 
 * Connect four wires: 
 * 
 * Arduino pin D14/SDA to RFD77402 SDA
 * Arduino pin D15/SCL to RFD77402 SCL
 *         Arduino GND to RFD77402 GND
 *         Arduino 3V3 to RFD77402 3V3
 * 
 */

#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
RFD77402 myDistance; //Hook object to the library

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("RFD77402 Read Example");

  if (myDistance.begin() == false)
  {
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Sensor online!");
}

void loop()
{
  myDistance.takeMeasurement(); //Tell sensor to take measurement

  unsigned long distance = myDistance.getDistance(); //Retrieve the distance value

  //Serial.print("distance: ");
  //Serial.print(distance);
  //Serial.print("mm");
  //Serial.println();
  distance = (distance*150)/2500;
  for(int i = 0; i < distance; i++)
    Serial.print('*');
  Serial.println();
}
