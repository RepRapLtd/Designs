//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>
#include <string.h>



/*I2C Address of the controller */
const int slaveAddress = 5;
long vTransmit;          // Max value 99,999,999
int loopTiming = 4;
int currentTime;
int transmitLoop = 1;
int pinClock = 13;
int pinDIR = 12;
//char vTransmitStringContents[20];
long vTransmitLength;
int slaveSignal;
//char vTransmitString[20];

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("");
  lineBreak(1);
  Serial.print("Begin ");
  pinMode(pinClock, OUTPUT);
  pinMode(pinDIR, OUTPUT);
  digitalWrite(pinDIR, HIGH);
  }

void sendSettings(){


  if (vTransmit < 256) {vTransmitLength = 1;}
  else if (vTransmit < 65536) {vTransmitLength = 2;}
  else if (vTransmit < 16777216) {vTransmitLength = 3;}
  else if (vTransmit < 4294967296) {vTransmitLength = 4;}
  else {vTransmitLength = 5;}
/*
  if (vTransmit < 10 ) { vTransmitLength = vTransmitLength *10;}
  else if (vTransmit < 100 ) {vTransmitLength = vTransmitLength * 100;}
  else if (vTransmit < 1000 ) {vTransmitLength = vTransmitLength * 1000;}
  else if (vTransmit < 10000 ) {vTransmitLength = vTransmitLength * 10000;}
  else if (vTransmit < 100000 ) {vTransmitLength = vTransmitLength * 100000;}
  else if (vTransmit < 1000000 ) {vTransmitLength = vTransmitLength * 1000000;}
  else if (vTransmit < 10000000 ) {vTransmitLength = vTransmitLength * 10000000;}
  else if (vTransmit < 100000000 ) {vTransmitLength = vTransmitLength * 100000000;}
  else if (vTransmit < 1000000000 ) {vTransmitLength = vTransmitLength * 1000000000;}
  else if (vTransmit < 10000000000 ) {vTransmitLength = vTransmitLength * 10000000000;}
  else if (vTransmit < 100000000000 ) {vTransmitLength = vTransmitLength * 100000000000;}
  else if (vTransmit < 1000000000000 ) {vTransmitLength = vTransmitLength * 1000000000000;}
  else if (vTransmit < 10000000000000 ) {vTransmitLength = vTransmitLength * 10000000000000;}
  else if (vTransmit < 100000000000000 ) {vTransmitLength = vTransmitLength * 100000000000000;}
  else if (vTransmit < 100000000000000 ) {vTransmitLength = vTransmitLength * 1000000000000000;}
  else {vTransmitLength = vTransmitLength * 10000000000000000;}*/

  //vTransmit = vTransmit + vTransmitLength;

  Wire.beginTransmission(slaveAddress);       // Open transmission to Slaveaddress
  //Wire.write(vTransmitLength);
  Wire.write(vTransmit);
  Wire.endTransmission();
  lineBreak(1);
  Serial.print("Sent: ");
  //Serial.print(vTransmitLength);
  Serial.print(vTransmit);
  //vTransmit = vTransmit - vTransmitLength;

  slaveSignal = voltageReading();
  Serial.print(" - receieved: "); Serial.print(slaveSignal);
  /*Wire.beginTransmission(slaveAddress);       // Open transmission to Slaveaddress
  itoa(vTransmit, vTransmitStringContents, 10);       // Convert vTransmit to a string
  int length = strlen(vTransmitStringContents);       // Measure the length of the string
  itoa(length, vTransmitStringLength, 10);    // Convert the length integer to a string
  vTransmitString = vTransmitStringLength + vTransmitStringContents;
  Wire.write(vTransmitString);
  Wire.endTransmission();
  lineBreak(1);
  Serial.print("Sent: ");
  Serial.print(vTransmitString);
*/
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
  //slaveSignal = Wire.read();
  //return slaveSignal;
}



void pulse(){
  digitalWrite(pinClock, HIGH);
  delay(loopTiming/2);
  digitalWrite(pinClock, LOW);
  delay(loopTiming/2);
}

void loop() {
  pulse();
  if (transmitLoop > 500) {transmitLoop = 1;} else {transmitLoop = transmitLoop + 1;}
  if (transmitLoop == 1) {
      if (vTransmit == 1) {vTransmit = 260;} else {vTransmit = 1;}
      sendSettings();
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


/*void inputCheck(){

    if (Serial.available() > 0) {
  int d = 0;
  lineCounter = 0;
  while (Serial.available()) { // slave may send less than requested   
    pSettingNewChar[d] = Serial.read(); // receive a byte as character
    d++;
  }
  pSettingNewChar[d] = 0;

  pSettingNew = atoi(pSettingNewChar);            // Convert input to number
  lineBreak(2); 
  Serial.print("Input: ");
  Serial.print(pSettingNewChar);
  if (pSettingNew <= pMax && pSettingNew >= pMin){ // Check input is within pressure setting range
    pSetting = pSettingNew;
    lineBreak(1);
    Serial.print("New pressure setting entered. Pressure setting ");
    Serial.print(pSetting);
    Serial.print(" to send to controller");
    lineBreak(2);
    } else {
    
    
    
    if (pSettingNew >= actionCodeStart && pSettingNew < pMin) { // If input is not within pressure setting range, check for valid action code
      actionCodeWrite();
    }
    
    else {lineBreak(1); Serial.print("!!! Invalid pressure input !!! "); inputPrompt();  } // Tell user to use valid input
    }
    } 
}*/

