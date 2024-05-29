
#include <stdio.h>
#include <TinyWireS.h>

// Voltage Regulator for ATTiny
// RepRap Ltd

const int slaveAddress = 8;


int masterSignal;
const int anOut = 1; // Output pin - NB do not change; only pins 0 and 1 can handle PWM and pin 0 is needed for I2C
int vSetting;
int vReading;



void setup() {
  TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
  pinMode (anOut, OUTPUT);


}


void loop() {
  if(TinyWireS.available() > 0 ) {      // Check for master sending pressure setting
    vReading = TinyWireS.receive(); // Read pressure setting
    vSetting = vReading;  // Convert signal to vReading
  }
    controlPulse();
    tws_delay(10);
}

  
void controlPulse(){
  analogWrite(anOut, vSetting);
 }



void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", vSetting);
  sprintf(s, "%4d \n", vSetting);
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


