// Include the required Wire library for I2C
#include <Wire.h>
int x;
int ip;
int y;
int slaveAddress;

void setup() {
  // Start the I2C Bus as Master
  x = 2;
  slaveAddress = 9;
  Serial.begin(9600);
  Wire.begin(); 
}
void loop() {
  if(Serial.available() > 0)
  {
    ip = Serial.read();
    if(ip != '\n')
       x = ip -'0';
  }
  Wire.beginTransmission(slaveAddress); // transmit to device #slaveAddress
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting
  delay(100);
  //Serial.println((char)(x + '0'));
  y = Wire.read(); 
  Serial.println((char)(y + '0'));
  delay(100);

}
