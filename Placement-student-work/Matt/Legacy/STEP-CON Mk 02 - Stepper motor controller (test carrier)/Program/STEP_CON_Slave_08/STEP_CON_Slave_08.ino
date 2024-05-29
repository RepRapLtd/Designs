

#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <EEPROM.h>

#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions



const int pinREF = 1;         // PWM for setting REF voltage
const int pinDIR = 5;         // Digital output to set direction
const int pinSTEP = 4;        // Digital wave output to trigger stepping

const int pinClock = 0;       // Clock input for step



void setup()  { 



  pinMode(pinREF, OUTPUT);
  pinMode(pinSTEP, OUTPUT);
  pinMode(pinDIR, OUTPUT);
  digitalWrite(pinREF, LOW);
  digitalWrite(pinSTEP, LOW);
  digitalWrite(pinDIR, LOW);



} 

// the loop routine runs over and over again forever:
void loop()  { 
     

  }



