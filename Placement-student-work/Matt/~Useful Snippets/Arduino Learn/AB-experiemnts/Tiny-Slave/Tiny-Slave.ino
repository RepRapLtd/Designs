//#include <usiTwiSlave.h> //**!!!!!!!!!!!!!!!!!!!!! This was the problem
#include <TinyWireS.h>

// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.




void setup() {
  TinyWireS.begin(8);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
}

void loop() {
  tws_delay(100);
}

char* s="hello ";
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  int i=0;
  while(s[i])
  {
    TinyWireS.send(s[i]);
    i++;
  }
  //TinyWireS.write("hello "); // respond with message of 6 bytes
  // as expected by master
}


