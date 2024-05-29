
#include <stdio.h>
#include <TinyWireS.h>

// Pulse Controller for ATTiny
// RepRap Ltd

int masterSignal;
const int anOut = 1; // Motor output A
int pSetting = 100;
int slaveAddress = 8;
int pReading;



void setup() {
  TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
  pinMode (anOut, OUTPUT);


}


void loop() {
  if(TinyWireS.available() > 0 ) {      // Check for master sending pressure setting
    pReading = TinyWireS.receive(); // Read pressure setting
    pSetting = pReading;  // Convert signal to vReading
  }
    controlPulse();
    tws_delay(10);
}

  
void controlPulse(){
  analogWrite(anOut, pSetting);
 }



void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  sprintf(s, "%4d \n", pSetting);
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


