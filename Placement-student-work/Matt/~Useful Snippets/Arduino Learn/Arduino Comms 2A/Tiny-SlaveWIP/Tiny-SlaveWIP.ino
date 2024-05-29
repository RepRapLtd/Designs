//#include <usiTwiSlave.h> //**!!!!!!!!!!!!!!!!!!!!! This was the problem
#include <TinyWireS.h>

// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

int masterSignal;
int slaveSignal;
int slaveAddress = 8;
int LED = 3;




void setup() {
  TinyWireS.begin(8);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
}


void flash(int f){
    for(int i = 0; i < f; i++)
    {
      digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
      delay(13);                        // wait for the specified time
      digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
      delay(13);             // wait for the specified time}
    }
   }


void loop() {
  masterSignal = TinyWireS.receive();
  if (masterSignal > 10){
    flash(2);
  }
  else
  {
    flash(1);
  }
  tws_delay(100);
}


void sendEvent(){
  TinyWireS.send(slaveSignal);
}


// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
    slaveSignal = 11;
    sendEvent();

  }





