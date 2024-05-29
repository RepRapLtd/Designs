
#include <stdio.h>
#include <TinyWireS.h>

// Pressure Motor Controller for ATTiny
// RepRap Ltd

int masterSignal;
const int anInp = 3; // SDA input
const int anOutUp = 4; // Motor output A
const int anOutDn = 1; // Motor output b
int motorTiming; // Motor duration
//const int motorInterval = 500; //Time that the motor runs for small adjustments (500)
const double motorIntervalBoost = 0.01; // Modifies the time added for large adjustments
//const int motorIntervalMax = 1500; // Makes sure that the motor does not run for longer than a loop of the master device
int pSetting = 100;
bool pressureChanging = false;    // Determine whether a pressure change has been ordered
int pReadingLast;


int pError = 3;
int slaveAddress = 8;
int pReading;
int actionCodeStart = 124;
int actionCodeEnd = 169;
int currentCode = 0;


//ACTION CODES
int codeStop = 127;
int codeStart = 130;


void setup() {
  TinyWireS.begin(slaveAddress);                // join i2c bus with address #8
  TinyWireS.onRequest(requestEvent); // register event
  pinMode (anOutUp, OUTPUT);
  pinMode (anOutDn, OUTPUT);

}


#define AVE 5

int voltageReading(){
  int answer = 0;
  for(int n = 0; n < AVE; n++)
    answer += analogRead(anInp);
  return answer/AVE;

  
}


void loop() {
  pressureLossCheck();
  
  if(TinyWireS.available() > 0 ) {      // Check for master sending pressure setting
    masterSignal = TinyWireS.receive(); // Read pressure setting
    masterSignal = masterSignal*3+100;  // Convert signal to vReading
    if (currentCode == codeStop) {emergencyStopFunction();} else {
    if (masterSignal == codeStop) { 
      emergencyStopFunction();
      } else {
        if (masterSignal == codeStart){
          currentCode = 0; 
          } else {
          pressureChange();
          }
       }
    }
    
  }
}


void pressureLossCheck(){
if (pressureChanging == false) {                                 // Check to see if pressure is supposed to be changing
  pReadingLast = voltageReading();                                 // Save the previous pressure reading
  tws_delay(13);                                                  // Wait around .1 second
  pReading = voltageReading();                                     // Take a new pressure reading
    if (pReadingLast > pReading + 3) {emergencyStopFunction();}       // Compare the two and stop the controller if the pressure is decreasing too fast
  }
}

void pressureChange(){
    if (pSetting != masterSignal)         // Compare to current pressure reading
    {
    pressureChanging = true;            //
    pSetting = masterSignal;
    }
  controlPressure();
  }

  
void controlPressure(){
  pReading = voltageReading();
  if (pReading < pSetting - pError) {
    motorUp();
    } else {
      if (pReading > pSetting + pError) {
        motorDown();
        } else{
          motorStop(); 
          pressureChanging = false;
        }
     }
 }

void motorUp() {

  motorTiming = pSetting - pReading;
  //if (motorTiming <= 1) {motorTiming = 1;}
  digitalWrite(anOutUp, 1);
  digitalWrite(anOutDn, 0);
  tws_delay(motorTiming);
  motorStop();
  if(motorTiming<50){motorTiming=50;}
  tws_delay(motorTiming);

}


void motorDown() {
  motorTiming = pReading -pSetting;
  //if (motorTiming <= 1) {motorTiming = 1;}
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 0);
  tws_delay(motorTiming);
  motorStop();
  if(motorTiming<100){motorTiming=100;}
  tws_delay(motorTiming);

}

void motorStop() {
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 1);
  tws_delay(5);

}




void emergencyStopFunction(){
  currentCode = codeStop;
  motorStop();
}





// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  if (currentCode<1){
    sprintf(s, "%4d \n", voltageReading());
    } else{
    sprintf(s, "%4d \n", currentCode);
    }
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


