//#include <usiTwiSlave.h> //**!!!!!!!!!!!!!!!!!!!!! This was the problem
#include <stdio.h>
#include <TinyWireS.h>

// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

int masterSignal;
const int anInp = 3; // SDA input
const int anOutUp = 4; // Motor output A
const int anOutDn = 1; // Motor output b
int motorPWM; // Motor power
int motorTiming; // Motor duration
const int motorInterval = 500; //Time that the motor runs for small adjustments (500)
const double motorIntervalBoost = 5; // Modifies the time added for large adjustments
const int motorIntervalMax = 1500; // Makes sure that the motor does not run for longer than a loop of the master device
int pSetting = 100;
int startReading;
double pReadingMod = 0.415;
int pReadingModAdd = 19;
int pError = 10;
double pwmMod = 5;
int slaveAddress = 8;
int pReading;


void setup() {
  TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
  pinMode (anOutUp, OUTPUT);
  pinMode (anOutDn, OUTPUT);
  //startReading = voltageReading()-pReadingModAdd;
  //startReading = 11;
}


#define AVE 5

int voltageReading(){
  int answer = 0;
  for(int n = 0; n < AVE; n++)
    answer += analogRead(anInp);
  return answer/AVE;

  
}


void loop() {
  if(TinyWireS.available() > 0 ) {
    masterSignal = TinyWireS.receive(); 
  
  pSetting = masterSignal*2 + 90;
  //if (pSetting = 92) {pSetting = 0;}
  monitorPressure();
  }
  }
  
void monitorPressure(){
  pReading = (voltageReading() - startReading)/pReadingMod;
  if (pReading < pSetting - pError) {motorUp();} else {
  if (pReading > pSetting + pError) {motorDown();} else{motorStop(); }}
 }

void motorUp() {

  masterSignal = pSetting - pReading;
  motorTiming = masterSignal *motorIntervalBoost;
  digitalWrite(anOutUp, 1);
  digitalWrite(anOutDn, 0);
  tws_delay(motorTiming);
  motorStop();

}


void motorDown() {
  masterSignal =  pReading - pSetting;
  motorTiming = masterSignal *motorIntervalBoost;
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 0);
  tws_delay(motorTiming);
  motorStop();

}

void motorStop() {
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 1);
  tws_delay(100);

}









/*void signalConvert(){
  if (masterSignal > 255) {motorPWM = 255;} else {motorPWM = masterSignal;}  // convert motor control signal (MCS) to PWM
  if (masterSignal > 255) {motorTiming = motorInterval + ((masterSignal - 255) * motorIntervalBoost);} else {motorTiming = motorInterval;} // Check timing on MCS - if MCS is greater than 255 then extra is added to the normal motor duration
  if (motorTiming > motorIntervalMax) {motorTiming = motorIntervalMax;} // Check that total motor duration is not more than the time that the master allocates per event
}*/

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  sprintf(s, "%4d \n", voltageReading());
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


