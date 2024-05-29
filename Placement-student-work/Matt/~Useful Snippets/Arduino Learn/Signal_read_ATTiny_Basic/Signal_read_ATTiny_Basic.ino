//#include <usiTwiSlave.h>
#include <TinyWireS.h>


/*

 */

int signalByte;
int LED;
int slaveAddress;


void setParams() {
    
    // SET THE PARAMETERS
     LED = 3;                 
    slaveAddress = 9;
    }  

// the setup function runs once when you press reset or power the board
void setup() {
  setParams();
  pinMode(LED, OUTPUT);      // initialize digital pin 13 as an output.
  TinyWireS.begin(slaveAddress);            // Set as Slave 9 on I2C
  //TinyWireS.onRequest(requestEvent);
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




// the loop function runs over and over again forever
void loop() {
  signalByte = TinyWireS.receive();
  signalByte = signalByte + 1;
    flash(2);
    TinyWireS.send(signalByte);
    //delay(500);
 }

