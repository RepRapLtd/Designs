int MotorA1 = 10; //top right
int MotorA2 = 9; //bottom right
int MotorB1 = 5; //top left
int MotorB2 = 6; //bottom left

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

long time0=micros();
for (int i=0; i<100; i++)
{myDistance.takeMeasurement(); //Tell sensor to take measurement

  unsigned long distance = myDistance.getDistance(); //Retrieve the distance value
}
long time1=micros();
Serial.print("microseconds; ");
Serial.println(time1-time0);
}



void loop() 
{
}

