// Include the required Wire library for I2C
#include <Wire.h>
int masterSignal;
int slaveSignal;
int slaveAddress;
int serialRate;
int LED;

void setParams(){
  masterSignal = 1;
  slaveAddress = 8;
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
  Wire.endTransmission();
  //delay(500);
    Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
  
  slaveSignal = Wire.read();
  //if (slaveSignal < 11) {slaveSignal = 0;} 
  Serial.print("Master: ");
  Serial.println((char)(masterSignal + '0'));
  Serial.print("Slave: ");
  if (slaveSignal < 0) {Serial.println("Minus 1!");  } 
  else {Serial.println((char)(slaveSignal + '0'));}
  }
  delay(900);
  LEDBlink();
  numberTest();
}
