int MotorA1 = 10; //top right
int MotorA2 = 9; //bottom right
int MotorB1 = 5; //top left
int MotorB2 = 6; //bottom left
int motorspeed=140;
int spintime=13500;

#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
RFD77402 myDistance; //Hook object to the library

void setup() 
{
 // put your setup code here, to run once:
pinMode(MotorA1, OUTPUT);
   pinMode(MotorA2, OUTPUT);
   pinMode(MotorB1, OUTPUT);
   pinMode(MotorB2, OUTPUT);


  Serial.begin(9600);
   while (!Serial);
  Serial.println("Frank");

  if (myDistance.begin() == false)
  {
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Sensor online!");
}

void Forward()

 {digitalWrite(MotorA1, LOW);
   digitalWrite(MotorA2, HIGH);
   digitalWrite(MotorB1, LOW);
   analogWrite(MotorB2, motorspeed);
 }

void Backward()

 {digitalWrite(MotorA1, HIGH);
   digitalWrite(MotorA2, LOW);
   analogWrite(MotorB1, motorspeed);
   digitalWrite(MotorB2, LOW);
 }

 void Stop()
 
 {digitalWrite(MotorA1, LOW);
   digitalWrite(MotorA2, LOW);
   digitalWrite(MotorB1, LOW);
   digitalWrite(MotorB2, LOW);
 }

void Clockwise()

 {digitalWrite(MotorA1, HIGH);
   digitalWrite(MotorA2, LOW);
   digitalWrite(MotorB1, LOW);
   analogWrite(MotorB2, motorspeed);
 }

void AntiClockwise()

 {digitalWrite(MotorA1, LOW);
   digitalWrite(MotorA2, HIGH);
   analogWrite(MotorB1, motorspeed);
   digitalWrite(MotorB2, LOW);
 }
void Bump()

{Clockwise();
long big=0;
long time0=millis();
unsigned long distance;
while(millis() < time0+spintime)
{myDistance.takeMeasurement(); //Tell sensor to take measurement
distance = myDistance.getDistance(); //Retrieve the distance value
if(distance>big)big=distance;
}
distance=0;
AntiClockwise ();
while(distance<(big*9)/10)
{myDistance.takeMeasurement(); //Tell sensor to take measurement
distance = myDistance.getDistance(); //Retrieve the distance value
}
Forward();
}

void loop() 
{
  myDistance.takeMeasurement(); //Tell sensor to take measurement

  unsigned long distance = myDistance.getDistance(); //Retrieve the distance value
  if (distance <300)
    Bump();
  else
    Forward();
 // put your main code here, to run repeatedly:
/* if (Serial.available() > 0) 
 {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the next ASCII value from what you received:
  switch (inChar)
  {
    case 'f':
    Forward ();
    break;
    case 'b':
    Backward ();
    break;
    case 's':
    Stop();
    break;
    default:
    Serial.println("wrong!");
  }
 }*/
}
