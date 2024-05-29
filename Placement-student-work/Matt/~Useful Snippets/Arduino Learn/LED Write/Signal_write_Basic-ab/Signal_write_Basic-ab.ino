// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}


/*int masterSignal;
int slaveSignal;
int slaveAddress;
int serialRate;
int LED;

void setParams(){
  masterSignal = 3;
  slaveAddress = 9;
  serialRate = 9600;
  LED = 13;
}


void setup() {
  // Start the I2C Bus as Master
  setParams();
  pinMode(LED, OUTPUT);
  Serial.begin(serialRate);
  Wire.begin(); 
  Serial.println("Open");
  Wire.onRequest(requestEvent);
}

void requestEvent(){
  digitalWrite(LED, HIGH);
  delay(900);
  digitalWrite(LED, LOW);
  delay(100);
}

void LEDBlink(){
  digitalWrite(LED, HIGH);
  delay(10);
  digitalWrite(LED, LOW);
  delay(20);
  digitalWrite(LED, HIGH);
  delay(20);
  digitalWrite(LED, LOW);
  delay(20);
  digitalWrite(LED, HIGH);
  delay(30);
  digitalWrite(LED, LOW);
  }

void numberTest(){
    if (masterSignal < 21) {masterSignal += 1;} else {masterSignal = 1;}
}

void loop() {
  Wire.beginTransmission(slaveAddress);
  Wire.write(masterSignal);
  Serial.print("Master: ");
  Serial.print(masterSignal);
  Wire.endTransmission();
  //while(Wire.available() <= 0);
  masterSignal = Wire.read();
  Serial.print(", Slave: ");
  Serial.println(masterSignal);
  if (masterSignal > 8 || masterSignal < 0) {masterSignal = 3;} 
  /*Serial.print("Slave: ");
  if (slaveSignal < 0) {Serial.println("Minus 1!");  } 
  else {Serial.println((char)(slaveSignal + '0'));}
  
  LEDBlink();
  numberTest();delay(900);
}*/
