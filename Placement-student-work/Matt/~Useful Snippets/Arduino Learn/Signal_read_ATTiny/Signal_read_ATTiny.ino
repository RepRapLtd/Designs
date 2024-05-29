//#include <usiTwiSlave.h>
#include <TinyWireS.h>


/*

 */

int signalByte;
int LED;
int y;
int slaveAddress;
int loopCounter;

void setParams() {
    
    // SET THE PARAMETERS
    loopCounter = 1;
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


void sendEvent(){
  TinyWireS.send(1);
  flash(2);
}

void receiveEvent(){
  signalByte = TinyWireS.receive();                    // read one character from the I2C
  flash(1);
}

void slaveTalk(){sendEvent();}



void masterTalk(){}



// the loop function runs over and over again forever
void loop() {

  receiveEvent();
  if (signalByte < 11) {masterTalk(); }
  else { slaveTalk();}
  loopCounter +=1;
  if (loopCounter > 60) {setup(); loopCounter = 1;}
}
