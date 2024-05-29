//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

int vReading;
int pSetting = 92;
int pReading;
double pReadingMod = 0.83;
int pReadingModAdd = 19;
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
int const actionCodeStart = 90;
int const pMax = 580;
int const pMin = 100;
int const emergencyStop = 90;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Serial.print("Open at ");
  Serial.print(voltageReading());
  Serial.print("/1000 for pressure setting ");
  Serial.print(pSetting);
  Serial.println("kPa");
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


void pIncrease(){
    vReading = voltageReading();
    pReading = vReading/pReadingMod;
    pwm = (pSetting - pReading) * pwmMod;
    Serial.print("Increase (");  
    Serial.print(vReading);
    Serial.print("/1000, ");
    if(pReading<pLowest) {Serial.print("<"); Serial.print(pLowest);} else {Serial.print(pReading);}
    Serial.print("kPa, motor control signal: ");
    Serial.print(pwm);
    Serial.println(")");
    delay(loopTiming);
    motorControl();
    }      

void pDecrease(){
    vReading = voltageReading();
    pReading = vReading/pReadingMod;
    pwm = (pSetting - pReading) * pwmMod;
    Serial.print("Decrease (");  
    Serial.print(vReading);
    Serial.print("/1000, ");
    Serial.print(pReading); 
    Serial.print("kPa, motor control signal: ");
    Serial.print(pwm);
    Serial.println(")");
    delay(loopTiming);
    motorControl();
    }


void pSteady(){
    vReading = voltageReading() ;
    pReading = vReading/pReadingMod;
    pwm = 0;
    Serial.print("Steady (");  
    Serial.print(vReading);
    Serial.print("/1000, ");
    Serial.print(pReading); 
    Serial.println("kPa)");
    delay(loopTiming);
    motorControl();
}



void motorControl(){
  Wire.beginTransmission(slaveAddress);
  pTransmit = pSetting/2 - 45;
  Wire.write(pTransmit);
  Serial.print("Sent: ");
  Serial.println(pSetting);
  Wire.endTransmission();
  }

void monitorPressure(){
  if (voltageReading()/pReadingMod < pSetting - pError) {pIncrease();} else {
  if (voltageReading()/pReadingMod > pSetting + pError) {pDecrease();} else{pSteady(); }}
 }

void loop() {

  if (Serial.available() > 0) {
  int d = 0;
  while (Serial.available()) { // slave may send less than requested   
    pSettingNewChar[d] = Serial.read(); // receive a byte as character
    d++;
  }
  pSettingNewChar[d] = 0;

  pSettingNew = atoi(pSettingNewChar);            // Convert input to number
  if (pSettingNew < pMax && pSettingNew >= pMin){ // Check input is within pressure setting range
    pSetting = pSettingNew;
    lineBreak();
    Serial.print("New pressure setting entered. Pressure setting ");
    Serial.print(pSetting);
    Serial.println(" to send to controller");
    lineBreak();
    } else {
    
    
    
    if (pSettingNew >= actionCodeStart && pSettingNew < pMin) { // If input is not within pressure setting range, check for valid action code
      actionCodes();
    }
    
    else { // If not valid, print warning
    lineBreak();
    Serial.print("Invalid pressure input! Please use an input between ");
    Serial.print(pMin);
    Serial.print(" and ");
    Serial.print(pMax);
    Serial.print(" or a valid action code between ");
    Serial.print(actionCodeStart);
    Serial.print(" and ");
    Serial.print(pMin - 2);
    lineBreak();  lineBreak();}
    }
    }  
    monitorPressure();
  delay(loopTiming);
  }

void actionCodes(){
      if (pSettingNew = emergencyStop) {
      pSetting = pSettingNew;
      lineBreak();
      Serial.print("EMERGENCY STOP");
      lineBreak(); lineBreak();
    }
    
}
 
void lineBreak(){
Serial.println(" ");
}
 


