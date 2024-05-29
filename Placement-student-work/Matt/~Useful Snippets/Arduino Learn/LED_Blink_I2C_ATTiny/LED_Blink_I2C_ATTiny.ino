#include <usiTwiSlave.h>
#include <TinyWireS.h>


/*

 */

double blinkTimer;      // Define the variable that controls the blink length
int blinkStartLength;   // Define the starting length
double blinkReduce;     // Define the variable that controls the percentage by which the timing gets shorter each time
double blinkOff;        // Define the variable that controls the difference between the on and off phases
int x;
int LED;
int y;

void setTimer() {
    
    // SET THE PARAMETERS
    
    blinkOff = 1;                       // Set the difference between the on and off phases
    blinkStartLength = 200;               // Define default start delay
    LED = 3;                 // Set LED as pin 13 
    y = 1;
    
    blinkTimer = blinkStartLength;        // Set the timer to the default

   
    }  

// the setup function runs once when you press reset or power the board
void setup() {
  setTimer();
  pinMode(LED, OUTPUT);      // initialize digital pin 13 as an output.
  TinyWireS.begin(9);            // Set as Slave 9 on I2C

  
}


void errorFlash(){
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(6);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(6);             // wait for the specified time}
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(13);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(13);             // wait for the specified time}
}


void signalFlash(){
    x = TinyWireS.receive();                    // read one character from the I2C
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(x * 133);                           // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(62);                                // wait for the specified time
    if (y > 8) {
      y = 1;
    } else {
      y = y + 1;
    }
  TinyWireS.send(y);
}

// the loop function runs over and over again forever
void loop() {
 

if (TinyWireS.available()>0) { signalFlash(); }    // Check for I2C input
else {errorFlash();}                          //Flash if no I2C signal is avaiable 

  /*if (blinkTimer>10) {                        // This will reset the 
    digitalWrite(LED, HIGH);                  // turn the LED on (HIGH is the voltage level)
    delay(blinkTimer);                        // wait for the specified time
    digitalWrite(LED, LOW);                   // turn the LED off by making the voltage LOW
    delay(blinkTimer * blinkOff);             // wait for the specified time
    blinkTimer = blinkTimer-(x*10);      //Change the delay
    if (blinkTimer>6000){
      blinkTimer = blinkStartLength;
      }
    
    } else {
      blinkTimer = blinkStartLength;
    }
  */
  }
