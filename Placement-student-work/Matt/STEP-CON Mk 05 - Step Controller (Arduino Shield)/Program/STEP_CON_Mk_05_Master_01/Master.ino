#include "WirePacket.h"

#define COMMAND_LENGTH 10

char data[DATA_LENGTH];
char command[COMMAND_LENGTH];
int cp;

const int slave1 = 8;
bool tick = false;
int tickTime = 2000; // us
const int clockPin = ??;
long nextTick;

void Clear()
{
  for(int i = 0; i < DATA_LENGTH; i++)
    data[i] = 0;
  for(int i = 0; i < COMMAND_LENGTH; i++)
    command[i] = 0;
  cp = 0;     
}

void Act()
{
  data[0] = command[0] - '0';
     
  switch(command[0])
  {
    case '2':
       if(command[1])
        data[1] = command[1] - '0';
      if(command[2])
        data[2] = command[2] - '0';
      if(command[3])
        data[3] = command[3] - '0';       
    case '0':
    case '1':
    case '4':
    case '5':
      WirePacket->Send(slave1, data, success);
      break;


    case '3':
      //data[1] = atoi(&command[1]);
      WirePacket->Send(slave1, data, success);

      if(WirePacket->Get(slave1, data))
      {
        Serial.print("PWM: ");
        Serial.println((int)data[0]);
      } else
        Serial.println("No reply.");
      break;

    case '6':
      WirePacket->Send(slave1, data, success);
      if(WirePacket->Get(slave1, data))
      {
        Serial.print("data was: ");
        for(int i = 0; i < DATA_LENGTH; i++)
        {
          Serial.print(data[i], HEX);
          Serial.print(' ');
        }
        Serial.println();
      } else
        Serial.println("No reply.");
      break;

    case 7:
      tick = true;
      break;

    case 8:
      tick = false;
      break;

    default:
      Serial.println("Commands:");
      Serial.println(" 0 - motor off");
      Serial.println(" 1 - motor on"); 
      Serial.println(" 2nnn - set pwm to nnn mv (must have leading zeros)"); 
      Serial.println(" 3 - return pwm"); 
      Serial.println(" 4 - motor forwards"); 
      Serial.println(" 5 - motor backwards");
      Serial.println(" 6 - retrieve last data sent");
      Serial.println(" 7 - clock on");
      Serial.println(" 8 - clock off");      
      Serial.println(" ? - print this list");      
  }
  Clear();
}
  
void setup() 
{
  WirePacket = new WPac();
  Serial.begin(115200);
  Clear();
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, 1);
  command[0] = '?';
  command[1] = 0;
  Act();
  nextTick = micros() + tickTime;
}

long t;

void loop() 
{
  WirePacket->Spin();

  if(nextTick - (t = micros()) <= 0)
  {
     nextTick = t + tickTime;
     if(tick)
     {
	digitalWrite(clockPin, 0);
        digitalWrite(clockPin, 1);
     }
  }
  
  if(Serial.available())
  {
    char c = Serial.read();
    if(c == '\n')
    {
      command[cp] = 0;
      cp = 0;
      Act();
    } else
    {
      command[cp] = c;
      cp++;
    }
  } 
}

