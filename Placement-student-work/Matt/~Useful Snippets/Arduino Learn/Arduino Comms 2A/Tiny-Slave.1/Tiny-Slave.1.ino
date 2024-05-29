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
const int motorInterval = 500; //Time that the motor runs for small adjustments
const int motorIntervalBoost = 1; // Modifies the time added for large adjustments
const int motorIntervalMax = 1500; // Makes sure that the motor does not run for longer than a loop of the master device

void setup() {
  TinyWireS.begin(8);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
  pinMode (anOutUp, OUTPUT);
  pinMode (anOutDn, OUTPUT);
}


#define AVE 5

int voltageReading(){
  int answer = 0;
  for(int n = 0; n < AVE; n++)
    answer += analogRead(anInp);
  return answer/AVE;
}


void loop() {
  masterSignal = TinyWireS.receive(); 
  if (masterSignal > 0) {motorUp();}
  if (masterSignal < 0) {motorDown();}
  if (masterSignal = 0) {motorStop();}
}

void motorUp() {
  signalConvert();
}


void motorDown() {
  masterSignal = 0 - masterSignal;
  signalConvert();
}

void motorStop() {
  
}

void signalConvert(){
  if (masterSignal > 255) {motorPWM = 255;} else {motorPWM = masterSignal;}  // convert motor control signal (MCS) to PWM
  if (masterSignal > 255) {motorTiming = motorInterval + ((masterSignal - 255) * motorIntervalBoost);} else {motorTiming = motorInterval;} // Check timing on MCS - if MCS is greater than 255 then extra is added to the normal motor duration
  if (motorTiming > motorIntervalMax) {motorTiming = motorIntervalMax;} // Check that total motor duration is not more than the time that the master allocates per event
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  char s[7];
  sprintf(s, "%4d \n", voltageReading());
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


