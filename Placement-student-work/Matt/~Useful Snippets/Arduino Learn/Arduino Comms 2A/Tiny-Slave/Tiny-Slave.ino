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


const int anInp = 3;

void setup() {
  TinyWireS.begin(8);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
}


#define AVE 5

int voltageReading(){
  int answer = 0;
  for(int n = 0; n < AVE; n++)
    answer += analogRead(anInp);
  return answer/AVE;
}


void loop() {
  tws_delay(10);
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


