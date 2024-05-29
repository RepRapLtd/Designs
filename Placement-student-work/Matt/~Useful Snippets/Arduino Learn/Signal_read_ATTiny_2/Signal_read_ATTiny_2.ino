#include <usiTwiSlave.h>
#include <TinyWireS.h>


/*

 */

int signalByte;
int LED;
int y;
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


void errorFlash(){
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(6);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(6);             // wait for the specified time}
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(6);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(6);             // wait for the specified time}
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(6);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(6);             // wait for the specified time}
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(6);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(6);             
    }

void onceFlash(){
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(13);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(13);             // wait for the specified time}
    }

void twiceFlash(){
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(13);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(13);             // wait for the specified time}
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(13);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(13);             // wait for the specified time}
    }

void sendEvent(){
  TinyWireS.send(signalByte);
  twiceFlash();
}

void receiveEvent(){
  signalByte = TinyWireS.receive();                    // read one character from the I2C
  onceFlash();
}

void slaveTalk(){sendEvent();}



void masterTalk(){}



// the loop function runs over and over again forever
void loop() {
  receiveEvent();
  if (signalByte < 100){slaveTalk();}
  else {masterTalk();}
  
  
  
  }
