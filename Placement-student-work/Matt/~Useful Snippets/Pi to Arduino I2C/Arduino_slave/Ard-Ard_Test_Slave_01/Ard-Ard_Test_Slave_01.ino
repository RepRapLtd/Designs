#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>


int slaveAddress = 8;
long currentTime;
int lineCounter=6;
int slaveSignal = 100;


void setup() {
  Wire.begin(slaveAddress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event 
  Serial.begin(9600);           // start serial for output
    Serial.println("");
  lineBreak(1);
  Serial.print("Begin ");
}

void loop() {
  Serial.print("."); lineCounter ++;
  if(lineCounter>100){lineBreak(1); lineCounter=0;}
  delay(500);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  lineBreak(1);
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.print(x);         // print the integer
}




void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  sprintf(s, "%4d \n", slaveSignal);
  int n=0;
  while(s[n])
  {
    Wire.write(s[n]);
    n++;
  }
}











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
