#include "Buzz.h"
#include "Sense.h"

#define noOfSensors                 4
#define pinLED                      13
#define calcLow                     70.0
#define calcMod                     30.0
#define calcHigh                    255.0
#define pulseTotal                  100
#define pulseMod                    600
#define hardPWM                     255
#define fuzzyPWM                    180
#define printTime   /* ms */        5000
#define tolerance                   50.0
#define exToleranceAvg              5

Sense* sensor;
Sense* currentSensor;
Sense* printSensor;

bool fuzzy = false;
float oldDistance[noOfSensors];
float d;
bool CSVPrinting = false;    //Display every data point in format to export to CSV?
bool buzz = true; // Turn the buzzers on/off for testing

void setup() 
{
  Serial.begin(115200);
  if (CSVPrinting == false) {Serial.println("Set-up beginning"); Serial.println();}
  pinMode(pinLED, OUTPUT);

  sensor = 0;

  for(int count = 0; count < noOfSensors; count++)
  {
    sensor = new Sense(pinTriggerSet(count), pinReadSet(count), new Buzz(pinPWMSet(count)), sensor, count);
 
    if(!count)
       currentSensor = sensor;
  }
  currentSensor->SetNext(sensor);
  printSensor = currentSensor;
  //Show number of sensors on LED


  int i = 0;
  int p;
  if (CSVPrinting == false) {
  while (i < noOfSensors){
     if(i>1) {p = i + 7;} else {p = i + 5;}     
      digitalWrite(pinLED, HIGH);
      digitalWrite(p, HIGH);
      Serial.print(" Motor "); Serial.print(i); Serial.println(" test");
      delay(250);
      digitalWrite(pinLED, LOW);
      digitalWrite(p, LOW);
      delay(250);  
      oldDistance[i] = 150.0;
      i++;
       
  }
  Serial.println(); Serial.print(" Number of sensors: "); Serial.println(noOfSensors); Serial.println();
  }
  
  //Print CSV Headers
  if (CSVPrinting == true) {
    i = noOfSensors;
    Serial.print("Time, ");
    while (i > 0){
      i--;
      Serial.print("Sensor "); Serial.print(i); Serial.print(", ");
      
      }
      Serial.println(); 
  }

  
  if (CSVPrinting == false) {Serial.println("Set-up finished");Serial.println();Serial.println();}
}



void GetDistances()
{
   if(sensor->Distance() < 0)
  {
    if(sensor->TimeOut())
      sensor->Reset();
    return;
  }

  sensor = sensor->Next();

  if(sensor->Distance() >= 0)
    sensor->Trigger();
}

void PrintAll()
{
  Sense* p = printSensor;
  for(int count = 0; count < noOfSensors; count++)
  {
    p->PrintState();
    p = p->Next();  
  }
  Serial.println();
}

void loop() 
{

  GetDistances();

  if(!(millis()%printTime))
    if (CSVPrinting == false) {PrintAll();}
  
  currentSensor->Spin();
  long g = 0;
  long p = 0;
  int i;
  int sen = currentSensor->SensorNumber();
  if (fuzzy == true) {i = fuzzyPWM;} else {i = hardPWM;}
  d = currentSensor->Distance();
  if(d >= 0.0) //If d < 0, then it means sensor is busy
  {
      //if (d + tolerance > oldDistance[sen]) {d = oldDistance[sen];}
      if (fabs(d - oldDistance[sen]) > tolerance) {
        d = (d + (oldDistance[sen] * (exToleranceAvg-1)))/exToleranceAvg;
        } else {  
        d = (d + oldDistance[sen])/2;
        }
      if(d < LONG_DISTANCE)   //If d > 0 LONG_DISTANCE, then it is not longer accurate
      {
         p = pulseMod/sqrt(d);
        if (p > pulseTotal){p = pulseTotal;}
        g = pulseTotal + 1 - p;
        currentSensor->Buzzer()->SetGap(g);
        currentSensor->Buzzer()->SetDuration(p);
        if(buzz)
          currentSensor->Buzzer()->SetIntensity(i);
        else
          currentSensor->Buzzer()->SetIntensity(0);
      } else
        currentSensor->Buzzer()->SetIntensity(0);   
   oldDistance[sen] = d;     
  }

   if (CSVPrinting == true) {printCSV();}
  currentSensor = currentSensor->Next();

}


void printCSV(){
  int sen = currentSensor->SensorNumber();
  if (sen == noOfSensors - 1) {Serial.print(millis()); Serial.print(", ");}
  if (d >= 0) {
    Serial.print(d);
    }
   if (sen == 0) {
      Serial.println();
   } else {
      Serial.print(", ");
   }
  }

int pinPWMSet(int currentSensor){
    int p;
    if(currentSensor>1) {p = currentSensor + 7;} else {p = currentSensor + 5;} 
    return p;
  }

int pinTriggerSet(int currentSensor){
    int t;
    if (currentSensor < 3) {t = currentSensor + 2;} else {t = currentSensor + 4;}
    return t;
  }

int pinReadSet(int currentSensor){
    int r;
    r = currentSensor + 14;
    return r;
  }

