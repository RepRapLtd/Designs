// Include the required Wire library for I2C
#include <Wire.h>
int LED = 13;
int x;
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}
void loop() {
  Serial.write("loop\n");
  delay(1000);
  //If value received is 0 blink LED for 200 ms
  if (x = 0) {
    digitalWrite(LED, HIGH);
    Serial.write("High"+ x);
    delay(200);
    digitalWrite(LED, LOW);
    Serial.write("Low"+ x);
    delay(200);
  }
  //If value received is 3 blink LED for 400 ms
  if (x = 3) {
    digitalWrite(LED, HIGH);
    Serial.write("High"+ x);
    delay(1000);
    digitalWrite(LED, LOW);
    Serial.write("Low"+ x);
    delay(1000);
  }
}
