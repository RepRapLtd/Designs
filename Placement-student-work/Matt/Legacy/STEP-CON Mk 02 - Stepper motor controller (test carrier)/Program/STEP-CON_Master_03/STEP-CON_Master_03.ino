
//RepRap Ltd Pressure Controller


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>


/* calibration values*/
int calibAdd=0;
double calibMul=1;

/*Default opening pressure*/
const int pStart = 200;


/*Max and min allowable pressure */
const int pMax = 550;
const int pMin = 90;

/*I2C Address of the controller */
const int slaveAddress = 8;
int newLine = 4;


/*Variables */
bool showData = true;
int vReading;
int pSetting;
int pReading;
double pReadingMod;
int pReadingModAdd;
int startTime;
int currentTime;
char slaveSignal;
int loopTiming = 500;
int pTransmit;
char pSettingNewChar[7];
int pSettingNew;
int const actionCodeStart = 22;
double const pReadingModFixed = 1;
int const pReadingModAddFixed = 0;
int const codeList = 22;
int const codeStop = 24;
int const codeStart = 27;
int const codeData = 30;
int const codePressureList = 32;
int lineCounter;
int pMinIn = pMin-15; // Variation on pMin to allow for innacuracy in pressure sent before triggering actionCodes

void setup() {
  startTime = second();
  if (calibMul<0.1) {calibMul=1;}         // Check that a calibration multiplier has been used - without this pReadingMod would be 0!
  pReadingMod = pReadingModFixed / calibMul;
  pReadingModAdd = pReadingModAddFixed + calibAdd;
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("");
  lineBreak(1);
  Serial.print("Tip: Enter ");
  Serial.print(codeList);
  Serial.print(" for a list of action codes.");  
  lineBreak(2);
  Serial.print("Getting pressure reading from regulator...");
  checkOpenPressure();
  lineBreak(2);
  Serial.print("Open pressure setting at ");
  Serial.print(pSetting);
  Serial.print("kPa");
  lineBreak(3);
}


char volts[7];
int voltageReading(){
  Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device 
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    volts[d] = Wire.read(); // receive a byte as character
    d++;
  }
  volts[d] = 0;
  return atoi(volts);
}



void sendPressure(){
  Wire.beginTransmission(slaveAddress);
  //pTransmit = pSetting/2 - 45;
  if (pSetting < pMin) {
    pTransmit =(pSetting/pReadingModFixed+pReadingModAddFixed-100)/3;
  } else {
    pTransmit =(pSetting/pReadingMod+pReadingModAdd-100)/3;
  }
  Wire.write(pTransmit);
  Serial.print("s");
  Serial.print(pSetting);
  Serial.print(", ");
  Wire.endTransmission();
  lineCounter = lineCounter + 1;

 }

void monitorPressure(){
  pReading = (voltageReading() - pReadingModAdd)*pReadingMod;
  if (pReading < pMinIn) {actionCodeRead();}
  else{
  Serial.print("r");
  Serial.print(pReading);
  if(showData==true) {Serial.print(", ");} else {Serial.print(";  ");} // Ending character depends on whether more data follows
  }

}

void showDifference(){
  if (showData==true){
    Serial.print("d");
    if (pReading - pSetting > 0) {Serial.print("+");}
    if (pReading - pSetting == 0) {Serial.print("=");}
    Serial.print(pReading - pSetting);
    Serial.print(", ");}
}

void showPercentage(){
  int p;
if (showData==true){
  Serial.print("p");
  p  = ((pReading - pSetting)*100)/pSetting;
  if (p<0){p = 0-p;}
  Serial.print(p);
  Serial.print("%;  ");
}
}

void runLineCounter(){
    if (lineCounter >newLine) {
    lineBreak(1);
    lineCounter = 0;
    
  }
}

void loop() {

  inputCheck(); 
    monitorPressure();
  delay(loopTiming);
    sendPressure();
    showDifference();
    showPercentage();
    runLineCounter();
  }

void actionCodeWrite(){
      if (pSettingNew == codeStop) {
      pSetting = pSettingNew;
      lineBreak(1);
      Serial.print("EMERGENCY STOP");
      lineBreak(2);
    }

     if (pSettingNew == codeStart) {
      pSetting = pSettingNew;
      lineBreak(1);
      Serial.print("Machine Re-set");
      lineBreak(2);
    }

  if (pSettingNew == codeList) {
      lineBreak(1);
      Serial.print("List of Action Codes:");
      lineBreak(1);
      Serial.print(" > List codes: "); Serial.print(codeList); lineBreak(1);
      Serial.print(" > Emergency Stop: "); Serial.print(codeStop); lineBreak(1);
      Serial.print(" > Re-start: "); Serial.print(codeStart); lineBreak(1);
      Serial.print(" > Show/hide detailed data: "); Serial.print(codeData); lineBreak(1);
      Serial.print(" > List allowable pressure settings: "); Serial.print(codePressureList); lineBreak(1);
      lineBreak(2);
    }
    
   if (pSettingNew == codeData) {
        lineBreak(1);
        Serial.print("Detailed data ");
        if(showData == true){
          Serial.print("hidden");
          showData = false;
          newLine=newLine * 2;
        } else {
          Serial.print("un-hidden");
          showData = true;
          newLine=newLine / 2;
         }
        lineBreak(2);
        }

   if (pSettingNew == codePressureList) {
        lineBreak(1);
        Serial.print("Pressure Settings ");
        lineBreak(1);
        Serial.print(" > Minimum: "); Serial.print(pMin); Serial.print("kPa"); lineBreak(1);
        Serial.print(" > Maximum: "); Serial.print(pMax); Serial.print("kPa"); lineBreak(1);
        lineBreak(2);
        }

}
 

void actionCodeRead(){
  pReading = (voltageReading() - pReadingModAddFixed)*pReadingModFixed;  // Use un-calibrated pressure values
  lineBreak(2);
  Serial.print("Received from controller: ");
  Serial.print(pReading);

      if (pReading == codeStop) {
      pSetting = codeStop;
      lineBreak(2);
      Serial.print("!!! EMERGENCY STOP !!!");
      lineBreak(2);
      Serial.print("Disconnect power to the regulator and re-set the controller. ");
      lineBreak(1);
      Serial.print("Check air-line connections before re-starting the regulator.");
      lineBreak(1);
      }
}



void lineBreak(int f){
      for(int i = 0; i < f; i++)
    {
    currentTime = second() + minute()*60 + hour()*3600;
    Serial.println(" ");
    // Add the leading zeros
    if (currentTime<10000000) {Serial.print("0");}
    if (currentTime<1000000) {Serial.print("0");}
    if (currentTime<100000) {Serial.print("0");}
    if (currentTime<10000) {Serial.print("0");}
    if (currentTime<1000) {Serial.print("0");}
    if (currentTime<100) {Serial.print("0");}
    if (currentTime<10) {Serial.print("0");}
    Serial.print(currentTime);
    Serial.print("s:   ");
    }
}

void inputPrompt(){
    lineBreak(1);
    Serial.print("Please use an input between ");
    Serial.print(pMin);
    Serial.print(" and ");
    Serial.print(pMax);
    Serial.print(" or a valid action code between ");
    Serial.print(actionCodeStart);
    Serial.print(" and ");
    Serial.print(pMinIn);
    Serial.print(" (Enter ");
    Serial.print(codeList);
    Serial.print(" for a list of action codes)");
    lineBreak(2);  
  
}

void checkOpenPressure(){
    pReading = voltageReading();                                        // Prank call to wake the Tiny up
    delay(1000);                                                        // Wait for the Tiny to get out of bed
    pReading = (voltageReading() - pReadingModAdd)*pReadingMod;         // Check the opening pressure
    if (pReading < pMin) {pSetting = pMin;} else {pSetting = pReading;} // If the opening pressure is above the min setting, keep it there; otherwise set to min
}


void inputCheck(){

    if (Serial.available() > 0) {
  int d = 0;
  lineCounter = 0;
  while (Serial.available()) { // slave may send less than requested   
    pSettingNewChar[d] = Serial.read(); // receive a byte as character
    d++;
  }
  pSettingNewChar[d] = 0;

  pSettingNew = atoi(pSettingNewChar);            // Convert input to number
  lineBreak(2); 
  Serial.print("Input: ");
  Serial.print(pSettingNewChar);
  if (pSettingNew <= pMax && pSettingNew >= pMin){ // Check input is within pressure setting range
    pSetting = pSettingNew;
    lineBreak(1);
    Serial.print("New pressure setting entered. Pressure setting ");
    Serial.print(pSetting);
    Serial.print(" to send to controller");
    lineBreak(2);
    } else {
    
    
    
    if (pSettingNew >= actionCodeStart && pSettingNew < pMin) { // If input is not within pressure setting range, check for valid action code
      actionCodeWrite();
    }
    
    else {lineBreak(1); Serial.print("!!! Invalid pressure input !!! "); inputPrompt();  } // Tell user to use valid input
    }
    } 
}

