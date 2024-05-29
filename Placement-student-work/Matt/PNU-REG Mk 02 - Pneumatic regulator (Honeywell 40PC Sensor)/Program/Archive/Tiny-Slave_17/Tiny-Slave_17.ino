
#include <stdio.h>
#include <TinyWireS.h>

// Pressure Motor Controller for ATTiny
// RepRap Ltd

int masterSignal;
const int anInp = 3; // SDA input
const int anOutUp = 4; // Motor output A
const int anOutDn = 1; // Motor output b
int motorPWM; // Motor power
int motorTiming; // Motor duration
//const int motorInterval = 500; //Time that the motor runs for small adjustments (500)
const double motorIntervalBoost = 0.01; // Modifies the time added for large adjustments
//const int motorIntervalMax = 1500; // Makes sure that the motor does not run for longer than a loop of the master device
int pSetting = 100;
bool pressureChanging = false;    // Determine whether a pressure change has been ordered
bool emergencyStop = false;

int pError = 1;
double pwmMod = 5;
int slaveAddress = 8;
int pReading;
int actionCodeStart = 124;
int actionCodeEnd = 169;


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
  if(TinyWireS.available() > 0 ) {      // Check for master sending pressure setting
    masterSignal = TinyWireS.receive(); // Read pressure setting
    masterSignal = masterSignal*3+100;  // Convert signal to vReading
    if (emergencyStop == true) {emergencyStopFunction();} else {
    if (masterSignal == codeStop) { 
      emergencyStopFunction();
      } else {
        if (masterSignal == codeStart){
          emergencyStop = false; 
          } else {
          pressureChange();
          }
       }
    }
    
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

  masterSignal = pSetting - pReading;
  //motorTiming = masterSignal *  motorIntervalBoost;
  if (motorTiming > 100) {motorTiming = 100;}
  digitalWrite(anOutUp, 1);
  digitalWrite(anOutDn, 0);
  tws_delay(motorTiming);
  //motorStop();

}


void motorDown() {
  masterSignal =  pReading - pSetting;
  motorTiming = masterSignal *  motorIntervalBoost;
  //if (motorTiming > 10) {motorTiming = 10;}
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 0);
  tws_delay(motorTiming);
  motorStop();
  //tws_delay(motorTiming); //Pause the motor to allow the pressure to reduce

}

void motorStop() {
  digitalWrite(anOutDn, 1);
  digitalWrite(anOutUp, 1);
  tws_delay(5);

}




void emergencyStopFunction(){
  emergencyStop = true;
  motorStop();
}




/*void signalConvert(){
  if (masterSignal > 255) {motorPWM = 255;} else {motorPWM = masterSignal;}  // convert motor control signal (MCS) to PWM
  if (masterSignal > 255) {motorTiming = motorInterval + ((masterSignal - 255) * motorIntervalBoost);} else {motorTiming = motorInterval;} // Check timing on MCS - if MCS is greater than 255 then extra is added to the normal motor duration
  if (motorTiming > motorIntervalMax) {motorTiming = motorIntervalMax;} // Check that total motor duration is not more than the time that the master allocates per event
}*/

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  char s[7];
  //sprintf(s, "%4d \n", pSetting);
  sprintf(s, "%4d \n", voltageReading());
  int n=0;
  while(s[n])
  {
    TinyWireS.send(s[n]);
    n++;
  }
}


