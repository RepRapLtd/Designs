//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>


int slaveSignal;

/*I2C Address of the controller */
const int slaveAddress = 5;





void setup() {

  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("Begin");

}


void loop() {
  slaveSignal = voltageReading();
  Serial.println(slaveSignal);
  delay(2000);
  }
  

char volts[7];
int voltageReading(){
  Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device 
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    volts[d] = Wire.read(); // receive a byte as character
    d++;
  }
  volts[d] = 0;
  return atoi(volts);
}



