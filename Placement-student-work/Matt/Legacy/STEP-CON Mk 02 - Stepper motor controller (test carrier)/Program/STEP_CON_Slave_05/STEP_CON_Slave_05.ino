

#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <EEPROM.h>
#include <stdio.h>
#include <TinyWireS.h>
#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions


#define INTERNAL2V56NC (6)

int REFVoltage = 25;                 // Setting for REF voltage

const int PWMMod = 2.67;

const int pinREF = 1;         // PWM for setting REF voltage
const int pinDIR = 5;         // Digital output to set direction
const int pinSTEP = 4;        // Digital wave output to trigger stepping
const int stepTimer = 10;
const int pinClock = 3;    
const int slaveAddress = 8;   // I2C slave address   

bool stepRun = true;
bool stepForward = true;
bool stepOn = true;

int hiByte;      // These are used to store longer variables into EEPROM
int loByte;
int PWM;

int calibrationFactor = 0;    // This holds the Vref value in millivolts


void setup()  { 
    TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
    TinyWireS.onRequest(requestEvent);            // register event

    // High Speed PWM settings
      TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
      TCCR0B = 0<<WGM02 | 1<<CS00;
      TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;
      GTCCR = 1<<PWM1B | 2<<COM1B0;
    
    // Interrupt pin settings
      GIMSK = 0b00100000;                       // turns on pin change interrupts
      if (pinClock == 0) {PCMSK = 0b00000001;}  // turn on interrupts on pin
      if (pinClock == 1) {PCMSK = 0b00000010;}  // turn on interrupts on pin
      if (pinClock == 2) {PCMSK = 0b00000100;}  // turn on interrupts on pin
      if (pinClock == 3) {PCMSK = 0b00001000;}  // turn on interrupts on pin
      if (pinClock == 4) {PCMSK = 0b00010000;}  // turn on interrupts on pin
      sei();                                    // Enables interrupts

  // Pin definitions
      pinMode(pinREF, OUTPUT);
      pinMode(pinSTEP, OUTPUT);
      pinMode(pinDIR, OUTPUT);
      pinMode(pinClock, INPUT);

  analogReference(INTERNAL2V56NC);  // This sets the internal ref to be 2.56V (or close to this)
  delay(100);  // Wait a while for this to stabilise.
  
  // Read in the Calibration Factor
  hiByte = EEPROM.read(124);
  loByte = EEPROM.read(125); 
  
  setDIR();
  setREF();   
  calibrationFactor = (hiByte << 8)+loByte;  // Get the sensor calibrate value 
} 

// the loop routine runs over and over again forever:
void loop()  { 
     

  }

ISR(PCINT0_vect){
    if (digitalRead(pinClock) == HIGH) {stepOn = true;} else {stepOn = false;}      // Check whether clock pin is high or low
    if (stepRun == true) {                                                          // Check whether master has ordered stepping
      if (stepOn == true) {                                                         // Create step pulse
        digitalWrite(pinSTEP, HIGH);
        } else {
        digitalWrite(pinSTEP, LOW);
        }
      }
}

void setDIR(){
  if (stepForward == true) {digitalWrite(pinDIR, HIGH);} else {digitalWrite(pinDIR, LOW);}
}

void setREF(){
  PWM = REFVoltage/PWMMod;
  analogWrite(pinREF, PWM);   
}

/*void runStep(){
  if (stepRun == true){
    digitalWrite(pinSTEP, HIGH); 
    _delay_ms(stepTimer/2);
    digitalWrite(pinSTEP, LOW); 
    _delay_ms(stepTimer/2);
    } else {
    _delay_ms(stepTimer);  
    }
    
}*/

void requestEvent(){
  
}

