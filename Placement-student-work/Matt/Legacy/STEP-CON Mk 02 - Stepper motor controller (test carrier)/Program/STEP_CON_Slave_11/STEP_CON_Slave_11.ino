

#define F_CPU 8000000  // This is used by delay.h library


#include <stdio.h>
#include <TinyWireS.h>
#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions
#include <string.h>


#define SPECIAL '*'
#define MSOUT 10
#define STRING 0
#define NOSTRING 1
#define TIMEOUT 2
#define NOSPECIAL 3
#define OVERFLOW 4

int REFVoltage = 25;                 // Setting for REF voltage

const int PWMMod = 2.67;

const int pinREF = 1;         // PWM for setting REF voltage
const int pinDIR = 5;         // Digital output to set direction
const int pinSTEP = 4;        // Digital wave output to trigger stepping
const int stepTimer = 10;
const int pinClock = 3;    
const int slaveAddress = 5;   // I2C slave address   

bool stepRun = true;
bool stepForward = true;
bool stepOn = true;
int masterSignal = 0;
char masterSignalByte[7];
//int currentCode = 10;

int PWM;
int stringReturnValue;




void setup()  { 


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

    TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
    TinyWireS.onRequest(requestEvent);            // register event

  // Pin definitions
      pinMode(pinREF, OUTPUT);
      pinMode(pinSTEP, OUTPUT);
      pinMode(pinDIR, OUTPUT);
      pinMode(pinClock, INPUT);

  setDIR();
  setREF();   

} 


void sendString(char* s)
{
  TinyWireS.send(SPECIAL);
  TinyWireS.send((char)strlen(s));
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }  
}

int getString(char* s, int length)
{
  if(TinyWireS.available() > 0 ) 
  {
     char check = TinyWireS.receive();
     if(check != SPECIAL)
      return NOSPECIAL;
     long time = millis();
     bool timeOut = false;
     while(!TinyWireS.available() && !(timeOut = (millis() - time >= MSOUT)));
     if(timeOut)
        return TIMEOUT;
     int bytes = TinyWireS.receive();
     int d = 0;
     while(d < bytes && d < length-1)
     {
        while(!TinyWireS.available() && !(timeOut = (millis() - time >= MSOUT)));
        if(timeOut)
          return TIMEOUT;
        s[d] = TinyWireS.receive(); // receive a byte as character
        d++;
     }
     if(d >= length-1)
      return OVERFLOW;
     s[d] = 0;
     return STRING;    
   }
   return NOSTRING; 
}


// the loop routine runs over and over again forever:
void loop()  
{
  char s[20];
  if ((stringReturnValue = getString(s, 20)) == STRING)
  { 
    masterSignal = atoi(&s[2]);
    if (masterSignal == 1)
      stepRun = true;
    else
      stepRun = false;
  }
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

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  char s[20];
  
  switch(stringReturnValue)
  {
    case STRING:
          sprintf(s, "    string: %4d\n", masterSignal);
          break;
          
    case NOSTRING:
          sprintf(s, " no string: %4d\n", masterSignal);
          break;

    case TIMEOUT:
          sprintf(s, "   timeout: %4d\n", masterSignal);
          break;
          
    case NOSPECIAL:
          sprintf(s, "no special: %4d\n", masterSignal);
          break;

    case OVERFLOW:
          sprintf(s, "  overflow: %4d\n", masterSignal);
          break;

    default:
          sprintf(s, "       dud: %4d\n", masterSignal);
          break;
  }

  sendString(s);
}

