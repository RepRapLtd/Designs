//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

int vReading;
int pSetting = 195;
int pReading;
double pReadingMod = 0.415;
int pReadingModAdd = 19;
int pError = 10;
char slaveSignal;
int pwm;
double pwmMod = 5;
int startReading;
int pLowest = 80;
int slaveAddress = 8;
int loopTiming = 500;
int pTransmit;
int pSettingNew;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  //startReading = voltageReading()-pReadingModAdd;
  startReading = 11;
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
    vReading = voltageReading() - startReading;
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
    vReading = voltageReading() - startReading;
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
    vReading = voltageReading() - startReading;
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
  if ((voltageReading() - startReading)/pReadingMod < pSetting - pError) {pIncrease();} else {
  if ((voltageReading() - startReading)/pReadingMod > pSetting + pError) {pDecrease();} else{pSteady(); }}
 }

void loop() {

  if (Serial.available() > 0) {
  // read the incoming byte:
  pSettingNew = Serial.read();
  if (pSettingNew < 600 && pSettingNew > 92){
    pSetting = pSettingNew;
    } else {
    Serial.println("Invalid pressure input! Please use an input between 92 and 600");
    }
    }  
    monitorPressure();
  delay(loopTiming);
  }

  

