// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

int vReading;
int pSetting = 300;
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
int loopTiming = 5000;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  startReading = voltageReading()-pReadingModAdd;
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
  Wire.write(pwm);
  Serial.print("Sent: ");
  Serial.println(pwm);
  Wire.endTransmission();
  }

void monitorPressure(){
  if ((voltageReading() - startReading)/pReadingMod < pSetting - pError) {pIncrease();} else {
  if ((voltageReading() - startReading)/pReadingMod > pSetting + pError) {pDecrease();} else{pSteady(); }}
 }

void loop() {
  monitorPressure();
  delay(loopTiming);
}
