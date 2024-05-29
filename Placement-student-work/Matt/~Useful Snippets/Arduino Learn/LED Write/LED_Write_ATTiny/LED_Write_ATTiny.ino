#include <TinyWireM.h>
#include <USI_TWI_Master.h>


int x;
void setup() {
  // Start the I2C Bus as Master
  x = 2;
  TinyWireM.begin(); 
}
void loop() {
  TinyWireM.beginTransmission(9); // transmit to device #9
  TinyWireM.send(x);              // sends x 
  TinyWireM.endTransmission();    // stop transmitting
  delay(1000);
}
