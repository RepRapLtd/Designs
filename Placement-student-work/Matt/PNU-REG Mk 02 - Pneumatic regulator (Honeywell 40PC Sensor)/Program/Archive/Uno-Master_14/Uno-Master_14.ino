//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

int vReading;
int pSetting;
int pReading;
double pReadingMod = 0.83;
int pReadingModAdd = 74;
int pError = 10;
char slaveSignal;
int pwm;
double pwmMod = 5;
int pLowest = 80;
int slaveAddress = 8;
int loopTiming = 500;
int pTransmit;
char pSettingNewChar[7];
int pSettingNew;
int const actionCodeStart = 42;
int const pMax = 550;
int const pMin = 90;
int const codeStop = 44;
int lineCounter;
int pMinIn = pMin-4; // Variation on pMin to allow for innacuracy in pressure sent before triggering actionCodes

void setup() {
  pSetting = pMin;     // Start pressure at min setting
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.print("Open pressure setting at ");
  Serial.print(pSetting);
  Serial.print("kPa");
  lineBreak(2);  
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



void sendPressure(){
  Wire.beginTransmission(slaveAddress);
  //pTransmit = pSetting/2 - 45;
  pTransmit =(pSetting/pReadingMod+pReadingModAdd-100)/3;
  Wire.write(pTransmit);
  Serial.print("s");
  Serial.print(pSetting);
  Serial.print(", ");
  Wire.endTransmission();
  lineCounter = lineCounter + 1;

 }

void monitorPressure(){
  pReading = (voltageReading() - pReadingModAdd)*pReadingMod;
  if (pReading < pMinIn  && pReading >= actionCodeStart) {actionCodeRead();}
  else{
  Serial.print("r");
  Serial.print(pReading);
  Serial.print(", ");
  }

}

void showDifference(){
  Serial.print("d");
  if (pReading - pSetting > 0) {Serial.print("+");}
  if (pReading - pSetting == 0) {Serial.print("=");}
  Serial.print(pReading - pSetting);
  Serial.print("; ");
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
    Serial.print("New pressure setting entered. Pressure setting ");
    Serial.print(pSetting);
    Serial.println(" to send to controller");
    lineBreak(1);
    } else {
    
    
    
    if (pSettingNew >= actionCodeStart && pSettingNew < pMin) { // If input is not within pressure setting range, check for valid action code
      actionCodeWrite();
    }
    
    else { // If not valid, print warning
    lineBreak(1);
    Serial.print("Invalid pressure input! Please use an input between ");
    Serial.print(pMin);
    Serial.print(" and ");
    Serial.print(pMax);
    Serial.print(" or a valid action code between ");
    Serial.print(actionCodeStart);
    Serial.print(" and ");
    Serial.print(pMin - 2);
    lineBreak(1);  lineBreak(2);}
    }
    }  
    monitorPressure();
  delay(loopTiming);
    sendPressure();
    showDifference();
    runLineCounter();
  }

void actionCodeWrite(){
      if (pSettingNew = codeStop) {
      pSetting = pSettingNew;
      lineBreak(1);
      Serial.print("EMERGENCY STOP");
      lineBreak(2);
    }
    
}
 

void actionCodeRead(){
  lineBreak(2);
  Serial.print("Received from controller: ");
  Serial.print(pReading);

      if (pReading == codeStop) {
      pSetting = codeStop;
      lineBreak(1);
      Serial.print("EMERGENCY STOP");
      lineBreak(2);
      }
}



void lineBreak(int f){
      for(int i = 0; i < f; i++)
    {
    Serial.println(" ");
    }
}

