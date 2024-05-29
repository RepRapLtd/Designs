//RepRap Ltd Pulse Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>


int pSetting = 0;       //Pulse duration setting
const int pMod = 1;
int pTransmit;
int pReading;
char slaveSignal;
const int slaveAddress = 8;
char pSettingNewChar[7];
int lineCounter;
int pSettingNew; 
const int pMax = 255; 
const int pMin = 1;
const int loopTiming = 1000;


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.print("Open pressure setting at ");
  Serial.print(pSetting);
  Serial.print("s^-6");
  lineBreak(2);  
}


char confirm[7];
int confirmPSetting(){
  Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device 
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    confirm[d] = Wire.read(); // receive a byte as character
    d++;
  }
  confirm[d] = 0;
  return atoi(confirm);
}



void sendPSetting(){
  Wire.beginTransmission(slaveAddress);
  //pTransmit = pSetting/2 - 45;
  pTransmit =pSetting * pMod;
  Wire.write(pTransmit);
  Serial.print("s");
  Serial.print(pSetting);
  Serial.print(", ");
  Wire.endTransmission();
  lineCounter = lineCounter + 1;

 }

void monitorPSetting(){
  pReading = confirmPSetting()/pMod ;
  
  Serial.print("r");
  Serial.print(pReading);
  Serial.print(", ");


}



void runLineCounter(){
    if (lineCounter >7) {
    lineBreak(1);
    lineCounter = 0;
    
  }
}

void loop() {

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
    Serial.print("New pulse setting entered. Pressure setting ");
    Serial.print(pSetting);
    Serial.println(" to send to controller");
    lineBreak(1);
    } else {
    lineBreak(1);
    Serial.print("Invalid input! Please use an input between ");
    Serial.print(pMin);
    Serial.print(" and ");
    Serial.print(pMax);
    lineBreak(1);  lineBreak(2);
    }
  }
    monitorPSetting();
  delay(loopTiming);
    sendPSetting();
    runLineCounter();
  }


 

void lineBreak(int f){
      for(int i = 0; i < f; i++)
    {
    Serial.println(" ");
    }
}

