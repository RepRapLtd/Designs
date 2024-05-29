
#include <stdio.h>
#include <TinyWireS.h>

const int pinSDA = 0;       // I2C data line
const int pinControl = 1;   // Output for driving pulse
const int pinSCK = 2;       // I2C clock line
const int pinExtra = 3;     // Spare pin
const int pinSwitch = 4;    // Press switch on board
const int ledOn = 0;
const int ledOff = 1;
const double twsCorrection = 131;



void setup() {
  
  pinMode (pinControl, OUTPUT);
}

void loop() {
  digitalWrite(pinControl, ledOff);
  correctedDelay(1);
  digitalWrite(pinControl, ledOn);
  correctedDelay(1);
}



void correctedDelay(int f){
      for(int i = 0; i < f; i++)
    {
    tws_delay(twsCorrection);
    }
}




