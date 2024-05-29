
#include <stdio.h>
#include <TinyWireS.h>

const int pinSDA = 0;       // I2C data line
const int pinControl = 1;   // Output for driving pulse
const int pinSCK = 2;       // I2C clock line
const int pinExtra = 3;     // Spare pin
const int pinSwitch = 4;    // Press switch on board
const int ledOn = 0;
const int ledOff = 1;
const int slaveAddress = 9;
const double twsCorrection = 131;

int counter = 0;

void setup() {
  
  pinMode (pinControl, OUTPUT);

  TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
}

void loop() {
  counter = counter + 1;
  tws_millis(1);
}


void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  sprintf(s, "%4d \n", counter);
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}




// Implement a delay loop that checks for the stop bit (basically direct copy of the stock arduino implementation from wiring.c)
void tws_millis(unsigned long ms)
{
    uint16_t start = (uint16_t)micros();
    while (ms > 0)
    {
        TinyWireS_stop_check();
        if (((uint16_t)micros() - start) >= twsCorrection)
        {
            ms--;
            start += twsCorrection;
        }
    }
}
