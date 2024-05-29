//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>
#include <string.h>

#define SPECIAL '*'
#define MSOUT 10
#define STRING 0
#define NOSTRING 1
#define TIMEOUT 2
#define NOSPECIAL 3
#define OVERFLOW 4


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

void sendString(char* s)
{
  Wire.beginTransmission(slaveAddress);       // Open transmission to Slaveaddress
  Wire.write(SPECIAL);
  Wire.write((char)strlen(s));
  int n=0;
  while(s[n])
  {
    Wire.write(s[n]);
    n++;
  }
  Wire.endTransmission();  
}

int getString(char* s, int length)
{
  if(Wire.available() > 0 ) 
  {
     char check = Wire.read();
     if(check != SPECIAL)
      return NOSPECIAL;
     long time = millis();
     bool timeOut = false;
     while(!Wire.available() && !(timeOut = (millis() - time >= MSOUT)));
     if(timeOut)
        return TIMEOUT;
     int bytes = Wire.read();
     int d = 0;
     while(d < bytes && d < length-1)
     {
        while(!Wire.available() && !(timeOut = (millis() - time >= MSOUT)));
        if(timeOut)
          return TIMEOUT;
        s[d] = Wire.read(); // receive a byte as character
        d++;
     }
     if(d >= length-1)
      return OVERFLOW;
     s[d] = 0;
     return STRING;    
   }
   return NOSTRING; 
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





  // Wire.write(vTransmitLength);
  //Wire.write(vTransmit);
    
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
    sprintf(s, "%4d", vTransmit);

   sendString(s);

  //Serial.print("Sent: ");
  //Serial.print(s);
  //Serial.println("|");
  

  lineBreak(1);
  Serial.print("Sent: (");
  Serial.print(vTransmitLength);
  Serial.print(")");
  Serial.print(s);
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

char volts[20];
char s[20];
int voltageReading()
{
  int result = 0;
  Wire.requestFrom(slaveAddress, 19);    // request 6 bytes from slave device 
  switch(getString(volts, 20))
  {
    case STRING:
          sprintf(s, "string: %s\n", volts);
          result = atoi(&volts[2]);
          break;
          
    case NOSTRING:
          sprintf(s, "no string: %s\n", volts);
          break;

    case TIMEOUT:
          sprintf(s, "timeout: %s\n", volts);
          break;
          
    case NOSPECIAL:
          sprintf(s, "no special: %s\n", volts);
          break;

    case OVERFLOW:
          sprintf(s, "overflow: %s\n", volts);
          break;

    default:
          sprintf(s, "dud: %s\n", volts);
          break;
  }
  Serial.print(s);
  return result;
}

long nextChange;

void pulse()
{
  if(millis() - nextChange < 0)
    return;
  digitalWrite(pinClock, !digitalRead(pinClock));
  nextChange = millis() + loopTiming/2;
}

void loop() {
  //pulse();
  if (transmitLoop > 500) {transmitLoop = 1;} else {transmitLoop = transmitLoop + 1;}
  if (transmitLoop == 1) {
      if (vTransmit == 1) {vTransmit = 400;} else {vTransmit = 1;}
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

