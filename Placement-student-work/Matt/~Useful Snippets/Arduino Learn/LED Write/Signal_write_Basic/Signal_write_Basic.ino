


#include <Wire.h>




int masterSignal;
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
  masterSignal = Wire.read();
  Serial.print("Slave: ");
  Serial.println(masterSignal);
  LEDBlink();
  delay(1000);
    /*Serial.print("Slave: ");
  if (slaveSignal < 0) {Serial.println("Minus 1!");  } 
  else {Serial.println((char)(slaveSignal + '0'));}
  
  LEDBlink();
  numberTest();*/
  //delay(900);
}
