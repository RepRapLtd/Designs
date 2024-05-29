/*

 */
#include <Wire.h>
double blinkTimer;      // Define the variable that controls the blink length
int blinkStartLength;   // Define the starting length
double blinkReduce;     // Define the variable that controls the percentage by which the timing gets shorter each time
double blinkOff;        // Define the variable that controls the difference between the on and off phases
int x;
int LED;
int blinkTimerSimple;

void setTimer() {
    
    // SET THE PARAMETERS
    
    blinkOff = 1;                       // Set the difference between the on and off phases
    blinkStartLength = 1000;               // Define default start delay
    //blinkReduce = 15;                      // Set the percentage by which the timing gets shorter each time
    
    
    
    blinkTimer = blinkStartLength;        // Set the timer to the default
    //blinkReduce = (blinkReduce/100)+1;    // Change blinkReduce to the number by which the interval will actually be divided
   
    }  

// the setup function runs once when you press reset or power the board
void setup() {
  LED = 13;                 // Set LED as pin 13
  pinMode(LED, OUTPUT);      // initialize digital pin 13 as an output.
  Wire.begin(9);            // Set as Slave 9 on I2C
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  setTimer();
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C

  blinkReduce = x;
  blinkReduce = (blinkReduce/10)+1;    // Change blinkReduce to the number by which the interval will actually be divided
}

// the loop function runs over and over again forever
void loop() {
  Serial.write(x);
  if (blinkTimer>10) {                        // This will reset the 
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(blinkTimer);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(blinkTimer * blinkOff);             // wait for the specified time
    blinkTimerSimple = blinkTimer;
    blinkTimer = blinkTimer/blinkReduce;      //Change the delay
    if (blinkTimer>6000){
      blinkTimer = blinkStartLength;
      }
    
    } else {
      blinkTimer = blinkStartLength;
    }
  
  }
