/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

double blinkTimer;      // Define the variable that controls the blink length
int blinkStartLength;   // Define the starting length
double blinkReduce;     // Define the variable that controls the percentage by which the timing gets shorter each time
double blinkOff;        // Define the variable that controls the difference between the on and off phases


void setTimer() {
    
    // SET THE PARAMETERS
    
    blinkOff = 1;                       // Set the difference between the on and off phases
    blinkStartLength = 100;               // Define default start delay
    blinkReduce = 0;                      // Set the percentage by which the timing gets shorter each time
    
    
    
    blinkTimer = blinkStartLength;        // Set the timer to the default
    blinkReduce = (blinkReduce/100)+1;    // Change blinkReduce to the number by which the interval will actually be divided
   
    }  

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  setTimer();
}



// the loop function runs over and over again forever
void loop() {
  if (blinkTimer>10) {             // This will reset the 
    digitalWrite(13, HIGH);         // turn the LED on (HIGH is the voltage level)
    delay(blinkTimer);              // wait for the specified time
    digitalWrite(13, LOW);          // turn the LED off by making the voltage LOW
    delay(blinkTimer * blinkOff);            // wait for the specified time
    blinkTimer = blinkTimer/blinkReduce;    //Change the delay
    if (blinkTimer>6000){
      blinkTimer = blinkStartLength;
      }
    
    } else {
      blinkTimer = blinkStartLength;
    }
  
  }
