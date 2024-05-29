#include <TimeLib.h>

#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>


int counter = 0;
int slaveAddress = 9;
int counterReadInt; 
int startTime;
int currentTime;
int timeDifferential;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  startTime = second();
}

void loop() {
  // put your main code here, to run repeatedly:
  counterReadInt = counterReading();
 
  if (counterReadInt == 0) {
    timeDifferential = 0;
    counter = 0;
    startTime = second();
    }else{
    //if (timeDifferential=0) {timeDifferential= currentTime-counter;}
    counter = counter + 100;
    }
  currentTime = second()-startTime;

  
  delay(96);
  Serial.print(currentTime*1000);
  Serial.print(", ");
  Serial.print(counter);
  Serial.print(", ");  
  Serial.print(counterReadInt);
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
