
#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

int counter = 0;
int slaveAddress = 9; 



void setup() {
  // put your setup code here, to run once:
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

}

void loop() {
  // put your main code here, to run repeatedly:
  counter = counter + 1;
  delay(1000);
  Serial.print(counter);
  Serial.print(", ");
  Serial.print(counterReading());
  Serial.println("; ");
}



char counterRead[7];
int counterReading(){
  Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device 
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    counterRead[d] = Wire.read(); // receive a byte as character
    d++;
  }
  counterRead[d] = 0;
  return atoi(counterRead);
}
