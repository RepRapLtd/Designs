/*
 * Pneumatic pulse/pressure generator for Arduino Uno
 * 
 * Adrian Bowyer
 * RepRap Ltd
 * 1 June 2016
 * 
 * In pulsed mode this takes an interrupt from iPin and generates a positive pulse on oPin.  The pulse
 * is also output to the LED on lPin.
 *
 * The duration of the pulse in microseconds can be changed by sending an integer to Serial
 * terminated by \n.
 * 
 * Alternatively, in continuous mode, the air is on whenever iPin is low or the
 * button is pressed.
 * 
 * If pin sPin is grounded then a pulse chain is generated at 20 Hz.
 */

#define LEN 20 // Bytes in a short string

const int iPin = 11;
const int oPin = 9;
const int lPin = 13;
const int sPin = 12;

const long interval = 50;           // Interval in ms for 20 Hz
long pulse = 5000;                  // Default pulse in us.
long currentPulse = 0;              // Time to...
long oldPulse = 0;                  // ...switch off.
long currentInterval = 0;           // 20Hz...
long oldInterval = 0;               // ...timer
bool live = false;                  // Is a pulse active?
char inString[LEN];                 // For input number
int sCount = 0;                     // Byte counter
int c;                              // Byte for reading
long pulseCount = 0;                // Count of number of pulses sent
bool buttonPressed = false;         // Check when sIn changes
bool continuous = false;            // True for continuous air; false for pulsed
byte pinState = 1;                  // State of the input pin


//*****************************************************************************************
/*
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{    
     if(!digitalRead(iPin)) // Only respond to high->low transition
      PulseOn();
}
*/


// Called by an interrupt and by sPin being held low
 
void PulseOn()
{
  oldPulse = micros();
  digitalWrite(oPin, 1);
  digitalWrite(lPin, 1);
  pulseCount++;
  live = true;   
}

void PollHL()
{
  byte p;
  if((p = digitalRead(iPin)) != pinState)
  {
    if(!p)
      PulseOn();
    pinState = p;
  }
}

// Turn a pulse off when it's finished

void PulseOff()
{
  live = false;
  digitalWrite(oPin, 0);
  digitalWrite(lPin, 0);  
}

// Report the pulse count and set it to 0

void PulseReport()
{
  Serial.print(pulseCount);
  Serial.print(" pulses sent.\n");
  pulseCount = 0;
}

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(oPin, OUTPUT);
  pinMode(lPin, OUTPUT);
  pinMode(sPin, INPUT_PULLUP); 
  pinMode(iPin, INPUT_PULLUP); // NB - no pullup, as needs to interface with Duet/Due
  //pciSetup(iPin);
  //attachInterrupt(digitalPinToInterrupt(iPin), PulseOn, FALLING);
  Prompt();
  sCount = 0;   
}

void Prompt()
{
  Serial.println("\nCommands (follow by return):");
  Serial.println("    r: print report");
  Serial.println("    c: air on whenever input is on");
  Serial.println("    p: pulse air in response to input");
  Serial.println(" nnnn: set pulse length to nnnn microseconds");
  Serial.println("    ?: print this list");
}

void loop() 
{
  if(continuous)
  {
    if(!digitalRead(iPin) || !digitalRead(sPin))
      PulseOn();
    else
      PulseOff();    
  }else
  {
    PollHL();
    
    // If a pulse is live terminate it if it has gone on long enough
    
    if(live)
    {
      currentPulse = micros();
      if(currentPulse - oldPulse >= pulse)
        PulseOff();
    }
    
    // If we are at a 20Hz moment check sPin and generate a pulse if it is 0
    
    currentInterval = millis();
    if(currentInterval - oldInterval >= interval)
    {
      oldInterval = currentInterval;
      if(!digitalRead(sPin))
      {
        PulseOn();
      }
    }   
  }

  // Report pulse count when the button changes state

  if(buttonPressed)
  {
    if(digitalRead(sPin))
    {
      buttonPressed = false;
      PulseReport();
    }
  } else
  {
    if(!digitalRead(sPin))
    {
      buttonPressed = true;
      PulseReport();
    }    
  }

  // Read any bytes from Serial and use them to adjust the pulse length or switch mode
  
  if(Serial.available())
  {
    c = Serial.read();
    if(c == '\n')
    {
      inString[sCount] = 0;
      if(sCount)
      {
        sscanf(inString, "%d", &pulse);
        Serial.print("Pulse set to ");
        Serial.print(pulse);
        Serial.print(" us.\n");
      }
      sCount = 0;
    }
    
    if(isdigit(c)) // Ignore non-digits
    {
      inString[sCount] = (char)c;
      sCount++;
      if(sCount >= LEN)
      {
        sCount = 0; // Throw away buffer overruns
      }
    }

    // Check other commands from the serial interface
    
    if(c == 'r')
      PulseReport();
    if(c == 'c')
    {
      continuous = true;
      Serial.println("Continuous pressure on.");
    }
    if(c == 'p')
    {
      continuous = false;
      Serial.println("Pulsed pressure on.");
    }
    if(c == '?' || c == 'h')
      Prompt();
  }

}

