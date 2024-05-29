
#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>
#include <string.h>

int slaveAddress = 8;
int wireRead;
long currentTime;
int lineCounter=6;


void setup() {
  // put your setup code here, to run once:

  Wire.begin(slaveAddress);        // join i2c bus (address optional for master)
  Wire.onReceive(receiveEvent());
  Serial.begin(9600);  // start serial for output
  Serial.println("");
  lineBreak(1);
  Serial.print("Begin ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(wireRead>0){
      lineBreak(1); 
      Serial.print(wireRead); 
      wireRead = 0;}
  else
  {Serial.print("."); lineCounter ++;}
  
  if(lineCounter>100){lineBreak(1); lineCounter=0;}
  delay(100);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

/*void receiveEvent(int numBytes){
  wireRead=Wire.read();
}*/



void lineBreak(int f){
      for(int i = 0; i < f; i++)
    {
    currentTime = second() + minute()*60 + hour()*3600;
    Serial.println(" ");
    // Add the leading zeros
    if (currentTime<10000000) {Serial.print("0");}
    if (currentTime<1000000) {Serial.print("0");}
    if (currentTime<100000) {Serial.print("0");}
    if (currentTime<10000) {Serial.print("0");}
    if (currentTime<1000) {Serial.print("0");}
    if (currentTime<100) {Serial.print("0");}
    if (currentTime<10) {Serial.print("0");}
    Serial.print(currentTime);
    Serial.print("s:   ");
    }
}
