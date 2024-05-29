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
int vReadingDigit;
int pSetting = 500;
int pError = 50;
char slaveSignal;
const int upPin = 1;
const int downPin = 0;
int pwm;
double pwmMod = 0.4;
int startReading;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  startReading = voltageReading();
  Serial.print("Open at: ");
  Serial.println(startReading);
}


char volts[7];
int voltageReading(){
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    volts[d] = Wire.read(); // receive a byte as character
    d++;
  }
  volts[d] = 0;
  Serial.print("\n*** ");
  Serial.println(volts);
  return atoi(volts);
}


void pIncrease(){
    vReading = voltageReading() - startReading;
    pwm = (pSetting - vReading) * pwmMod;
    Serial.print("Increase (");  
    Serial.print(vReading); 
    Serial.print(", pwm: ");
    Serial.print(pwm);
    Serial.println(")");
    /*analogWrite(upPin, pwm);
    digitalWrite(downPin, 0);
    delay(100);
    stopMotor();*/
    }      

void pDecrease(){
    vReading = voltageReading() - startReading;
    pwm = (pSetting - vReading) * pwmMod;
    Serial.print("Decrease (");  
    Serial.print(vReading); 
    Serial.print(", pwm: ");
    Serial.print(pwm);
    Serial.println(")");

    }

void pSteady(){
    Serial.print("Steady (");  
    Serial.print(voltageReading()); 
    Serial.println(")");
    stopMotor();
}

void stopMotor(){
    digitalWrite(upPin, 1);
    digitalWrite(downPin, 1);
  
}

void motorControl(){
  if (voltageReading() - startReading < pSetting - pError) {pIncrease();} else {
  if (voltageReading() - startReading > pSetting + pError) {pDecrease();} else{pSteady(); }}
 }

void loop() {
  motorControl();
  delay(500);
}
