#include "WirePacket.h"

#define SLAVE_ADDRESS 18

char data[DATA_LENGTH];
char oldData[DATA_LENGTH];
volatile bool stepRun = false;
bool stepForward = true;

const float PWMMod = 2.5;
int voltagePWM;

/* OUTPUT */
  const int pinREF = 3;         // PWM for setting REF voltage
  const int pinDIR = A0;         // Digital output to set direction
  const int pinSTEP = A1;        // Digital wave output to trigger stepping (A1 on shield)

/* INPUT */
  const int pinClock = 2; 
/* TINY STUFF
ISR(PCINT0_vect)
{
  if(!stepRun || digitalRead(pinClock))
    return;
    
  // Create step pulse only on falling edge
  
  digitalWrite(pinSTEP, LOW);
  digitalWrite(pinSTEP, HIGH);
}
*/

void stepRunFunction(){
    if(stepRun == true) {
      digitalWrite(pinSTEP, LOW);
      digitalWrite(pinSTEP, HIGH);
    }
    
}

void setDIR()
{
  if (stepForward) 
  {
    digitalWrite(pinDIR, HIGH);
  } else 
  {
    digitalWrite(pinDIR, LOW);
  }
}

void setREF(float REFVoltage)
{
  voltagePWM = round(REFVoltage/PWMMod);
  analogWrite(pinREF, voltagePWM);   
  Serial.println("");
  Serial.print("REFVoltage: "); Serial.println(REFVoltage);
  Serial.print("voltagePWM: "); Serial.println(voltagePWM);
}

void PutVoltageInData()
{
  for(int i = 0; i < DATA_LENGTH; i++)
     data[i] = 0;
  float v = voltagePWM*PWMMod;
  if(v < 10.0)
    data[3] = (char)v;
  else if(v < 100.0)
  {
    data[2] = (char)(v/10.0);
    data[3] = (char)(v - data[2]*10);
  } else
  {
    data[1] = (char)(v/100.0);
    data[2] = (char)((v - data[1]*100)/10.0);
    data[3] = (char)(v - data[1]*100 - data[2]*10);
  }
}

void Act()
{
  char tempString[20];
  int v;
  
  switch(data[0])
  {
    case 0:
      stepRun = false;
      Serial.println("Stop");
      break;

    case 1:
      stepRun = true;
      Serial.println("Start");
      break;

    case 2:
      v = (int)data[1]*100 + (int)data[2]*10 + (int)data[3];
      setREF((float)v);
      //Serial.print("2");
      break;

    case 3:
      PutVoltageInData();
      WirePacket->Send(data, success);
      //Serial.print("3");
      break;

    case 4:
      stepForward = true;
      setDIR();
      Serial.println("Forward");
      break;

    case 5:
      stepForward = false;
      setDIR();
      Serial.println("Back");
      break;

    case 6:
      WirePacket->Send(oldData, success);
      Serial.println("Replied");
      break;  

    default:
       ;
  }
}
  
void setup() 
{
  TCCR2B = TCCR2B & B11111000 | B00000001;  
  WirePacket = new WPac(SLAVE_ADDRESS);

  pinMode(pinREF, OUTPUT);
  pinMode(pinSTEP, OUTPUT);
  digitalWrite(pinSTEP, 1);
  pinMode(pinDIR, OUTPUT);
  pinMode(pinClock, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinClock), stepRunFunction, FALLING);



/* TINY STUFF
// High Speed PWM settings
  TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
  TCCR0B = 0<<WGM02 | 1<<CS00;
  TCCR1 = 0<<PWM1A | 0<<COM1MA0 | 1<<CS10;
  GTCCR = 1<<PWM1B | 2<<COM1B0;
   
// Interrupt pin setting
  GIMSK = 0b00100000;
  PCMSK = 1 << pinClock;
*/ 

  
  for(int i = 0; i < DATA_LENGTH; i++)
    data[i] = 0;
  Act();
  setREF(50);
  setDIR();
  sei();         
}

void loop() 
{
  WirePacket->Spin();
  if(WirePacket->Get(data))
  {
    WirePacket->Print(data, success);
    Act();
    for(int i = 0; i < DATA_LENGTH; i++)
      oldData[i] = data[i];
  }
}




