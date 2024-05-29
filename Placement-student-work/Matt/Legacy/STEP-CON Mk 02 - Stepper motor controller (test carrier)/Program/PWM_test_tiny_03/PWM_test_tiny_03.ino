/*
 ATtiny85 test code
 
 Overview:
 This code flashes the LEDs and outputs data on the serial port.
 This is to test the function of the IC at lower voltages.
 
 This code is designed to run on the ATTiny 25/45/85
 The serial output only works with the larger ATTiny85 IC
 
 The connections to the ATTiny are as follows:
 ATTiny    Arduino    Info
 Pin  1  - 5          RESET / Rx (Not receiving any data)
 Pin  2  - 3          Tx for serial conenction
 Pin  3  - 4          FET driver (PWM)
 Pin  4  -            GND
 Pin  5  - 0          RED LED (PWM)
 Pin  6  - 1          GREEN LED
 Pin  7  - 2 / A1     Vsensor (Analog)
 Pin  8  -   +Vcc
 
 See www.samaenergy.org/www.re-innovation.co.uk for more details including flow code
 
 13/11/13 by Matt Little (matt@re-innovation.co.uk/www.re-innovation.co.uk)
 
 Updated:  
 13/11/13  Added fast PWM frequency - Matt Little

 
 This example code is in the public domain.
 */

#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <EEPROM.h>

#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions

// Only use Serial if using ATTiny85
// Serial output connections:
//#include <SoftwareSerial.h>
//#define rxPin 5    // We use a non-existant pin as we are not interested in receiving data
//#define txPin 3
//SoftwareSerial serial(rxPin, txPin);

#define INTERNAL2V56NC (6)

//************ USER PARAMETERS***********************

//**********MODE*************************************
//const int deviceType = 85;  // 45 = ATTiny45, NO serial output, 85 = AtTiny85, with serial output

// LED output pins:
const int redled = 1;         // Red LED attached to here (0, IC pin 5)
//const int buzzLedSw = 0;       // Green LED/buzzer/Switch attached to here (1, IC pin 6)

// MOSFET Driver output
//const int FETdriver = 4;

// Analog sensing pin
//const int VsensePin = A1;    // Reads in the analogue number of voltage
//long int VsenseValue = 0;   // Holds the voltage data
//unsigned long int Vint = 0;  //Holds the voltage as an int

//int voltageRange = 0;  // This stores the volatge range. This is 12V, 24V or 0v (error)
//const int Taverage = 10;  // This is the number of samples to average over (each sample is around 5ms)

/*// PID CONTROL values
int FETPWM = 0;      // This is the control for the PWM 
int integral = 0;    // Holds the integral part
int proportional = 0;// Holds the proportional part
int error = 0;  // Holds the error term*/

//Timing for serial output
//long int oldMillis = 0;  //This holds the previous millisecond count value

// Varibales for EEPROM
int hiByte;      // These are used to store longer variables into EEPROM
int loByte;

// Varibles for the calibration factor
int calibrationFactor = 0;    // This holds the Vref value in millivolts

// State machine control
//int stateControl = 0;  // This controls the state of the device

// the setup routine runs once when you press reset:
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
  
  // Set up IO pins
  //pinMode(rxPin, INPUT);
  //pinMode(txPin, OUTPUT);  
  pinMode(redled, OUTPUT);
  //pinMode(buzzLedSw, OUTPUT);        // First want to read the switch
  //pinMode(FETdriver, OUTPUT);
  
  //digitalWrite(FETdriver, LOW);   //  Switch the FET OFF
  
  /*if(deviceType==85)
  {
    // Start the serial output string - Only for ATTiny85 Version
    serial.begin(4800);
    serial.println("TEST ATTiny85");
    serial.println("13/11/13 Matt Little"); 
  }*/

  analogReference(INTERNAL2V56NC);  // This sets the internal ref to be 2.56V (or close to this)
  delay(100);  // Wait a while for this to stabilise.
  
  // Read in the Calibration Factor
  hiByte = EEPROM.read(124);
  loByte = EEPROM.read(125); 
  
  calibrationFactor = (hiByte << 8)+loByte;  // Get the sensor calibrate value 
  /*
  serial.print("Calibration Factor: ");   // TESTING
  serial.println(calibrationFactor);   // TESTING
  */
} 

// the loop routine runs over and over again forever:
void loop()  { 
  
    // RED LED ON  
    // set the output RED
    analogWrite(redled, 12);    // Set it to 50%  running at 31.2kHz  
    //analogWrite(buzzLedSw, 0); 
    _delay_ms(500);
    //serial.println("This is a NEW TEST");
    // GREEN LED ON  
    // set the output GREEN
    //analogWrite(redled, 0);    
    //analogWrite(buzzLedSw, 255);    
    //_delay_ms(500);
}
