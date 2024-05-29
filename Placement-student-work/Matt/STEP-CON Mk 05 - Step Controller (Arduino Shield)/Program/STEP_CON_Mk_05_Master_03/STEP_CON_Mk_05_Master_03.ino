#include "WirePacket.h"

#define COMMAND_LENGTH 10

#define MAX_AX 4

unsigned char data[DATA_LENGTH];
unsigned char command[COMMAND_LENGTH];
int cp;

const int slave1 = 15;
bool tick = false;
int tickTime = 2000; // us
const int clockPin = 3;
long nextTick;


void Clear()
{
  for(int i = 0; i < DATA_LENGTH; i++)
    data[i] = 0;
  for(int i = 0; i < COMMAND_LENGTH; i++)
    command[i] = 0;
  cp = 0;     
}

void loadData(unsigned char data[], long V){
  //Serial.println(V, HEX);
  for (int i = 3; i >= 0; i--){
    data[i] = V & 0xff;
    //Serial.print(" ");
    //Serial.print(data[i], HEX);
    V = V >> 8;
    }  
    //Serial.println(); 
  }


long oldPosition[MAX_AX];
int addresses[MAX_AX];

void MoveAxes(long newPosition[])
{
    long totalSteps = -1;
    long delta;
    int bigDirection;
    for(int axis = 0; axis < MAX_AX; axis ++)
    {
        delta = newPosition[axis] - oldPosition[axis];

        if(abs(delta) > totalSteps)
        {
            totalSteps = abs(delta);
            bigDirection = axis;
        }
        loadData(&data[1], delta);
        data[0] = 9;
        WirePacket->Send(addresses[axis], data, success);
    }

    if(totalSteps <= 0)
        return; // nothing to do


    for(int axis = 0; axis < MAX_AX; axis ++)
    {
        loadData(&data[1], totalSteps);
        data[0] = 10;
        WirePacket->Send(addresses[axis], data, success);
    }
    
    nextTick = micros() + tickTime;
    long t;
    
    while(totalSteps > 0)
    {
      if(nextTick - (t = micros()) <= 0)
      {
        nextTick = t + tickTime;
        digitalWrite(clockPin, 0);
        digitalWrite(clockPin, 1);
        totalSteps--;
      }
    }

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

    case '7':
      tick = true;
      break;

    case '8':
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
      Serial.println(" 9 - send test data");
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
        digitalWrite(clockPin, !digitalRead(clockPin));
        //Serial.println("*");
        //digitalWrite(clockPin, 1);
     }
  }
  
  if(Serial.available())
  {
    unsigned char c = Serial.read();
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

