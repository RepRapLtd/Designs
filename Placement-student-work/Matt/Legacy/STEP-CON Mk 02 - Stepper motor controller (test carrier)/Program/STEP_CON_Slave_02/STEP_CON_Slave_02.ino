

#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <EEPROM.h>

#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions


#define INTERNAL2V56NC (6)

int REFVoltage = 25;                 // Setting for REF voltage

const int PWMMod = 2.67;

const int pinREF = 1;         // PWM for setting REF voltage
const int pinDIR = 3;         // Digital output to set direction
const int pinSTEP = 4;        // Digital wave output to trigger stepping
const int stepTimer = 10;
const int pinClock = 0;       // Clock input for step

bool stepRun = true;
bool stepForward = true;

int hiByte;      // These are used to store longer variables into EEPROM
int loByte;
int PWM;

int calibrationFactor = 0;    // This holds the Vref value in millivolts


void setup()  { 


    /*
    Control Register A for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0A is 8 bits: [COM0A1:COM0A0:COM0B1:COM0B0:unused:unused:WGM01:WGM00]
    2<<COM0A0: sets bits COM0A0 and COM0A1, which (in Fast PWM mode) clears OC0A on compare-match, and sets OC0A at BOTTOM
    2<<COM0B0: sets bits COM0B0 and COM0B1, which (in Fast PWM mode) clears OC0B on compare-match, and sets OC0B at BOTTOM
    3<<WGM00: sets bits WGM00 and WGM01, which (when combined with WGM02 from TCCR0B below) enables Fast PWM mode
    */
    TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
   
    /*
    Control Register B for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0B is 8 bits: [FOC0A:FOC0B:unused:unused:WGM02:CS02:CS01:CS00]
    0<<WGM02: bit WGM02 remains clear, which (when combined with WGM00 and WGM01 from TCCR0A above) enables Fast PWM mode
    1<<CS00: sets bits CS01 (leaving CS01 and CS02 clear), which tells Timer/Counter-0 to not use a prescalar
    */
    TCCR0B = 0<<WGM02 | 1<<CS00;
   
    /*
    Control Register for Timer/Counter-1 (Timer/Counter-1 is configured with just one register: this one)
    TCCR1 is 8 bits: [CTC1:PWM1A:COM1A1:COM1A0:CS13:CS12:CS11:CS10]
    0<<PWM1A: bit PWM1A remains clear, which prevents Timer/Counter-1 from using pin OC1A (which is shared with OC0B)
    0<<COM1A0: bits COM1A0 and COM1A1 remain clear, which also prevents Timer/Counter-1 from using pin OC1A (see PWM1A above)
    1<<CS10: sets bit CS11 which tells Timer/Counter-1  to not use a prescalar
    */
    TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;
   
    /*
    General Control Register for Timer/Counter-1 (this is for Timer/Counter-1 and is a poorly named register)
    GTCCR is 8 bits: [TSM:PWM1B:COM1B1:COM1B0:FOC1B:FOC1A:PSR1:PSR0]
    1<<PWM1B: sets bit PWM1B which enables the use of OC1B (since we disabled using OC1A in TCCR1)
    2<<COM1B0: sets bit COM1B1 and leaves COM1B0 clear, which (when in PWM mode) clears OC1B on compare-match, and sets at BOTTOM
    */
    GTCCR = 1<<PWM1B | 2<<COM1B0;
    //_delay_ms(3000);
    GIMSK = 0b00100000;    // turns on pin change interrupts
    PCMSK = 0b00010001;    // turn on interrupts on pins PB0, , &amp;amp; PB4
    sei();                 // Enables interrupts


  pinMode(pinREF, OUTPUT);
  pinMode(pinSTEP, OUTPUT);
  pinMode(pinDIR, OUTPUT);

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

ISR(PCINT0_vect)
{
    if (stepRun == true) {digitalWrite(pinSTEP, HIGH);stepRun = false;} else {digitalWrite(pinSTEP, LOW);stepRun = true;}
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

