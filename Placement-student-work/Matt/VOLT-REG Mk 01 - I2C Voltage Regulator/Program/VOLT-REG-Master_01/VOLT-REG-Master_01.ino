//RepRap Ltd Voltage Regulator


#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>

/* !!!NB all voltage settings in mV!!! */



// Edit settings to optimise

const int vMax = 5000;        // Voltage delivered to ATTiny by power supply (max output allowable by program)
const int vMin = 1;           // Minimum output allowable by program
const int slaveAddress = 8;   // I2C address of the regulator
const int loopTiming = 1000;  // Time delay between each cycle
int vSetting = 0;             // Voltage setting - altered by user, but default value can be set here


// Variables used by program

double pMod;                  // Multiplier to change volts into PWM
int vTransmit;                // PWM setting to transmit
int vReading;                 // Voltage setting recieved from ATTiny
char vSettingNewChar[7];      // Reading from ATTiny
int lineCounter;              // Counts written data to split into lines
int vSettingNew;              // New voltage entered by user





void setup() {
  pMod = 255/vMax;
  Wire.begin();               // join i2c bus (address optional for master)
  Serial.begin(9600);         // start serial for output
  Serial.print("Open pressure setting at ");
  Serial.print(vSetting);
  Serial.print("mV");
  lineBreak(2);  
}


char confirm[7];
int confirmVSetting(){
  Wire.requestFrom(slaveAddress, 6);    // request 6 bytes from slave device 
 int d = 0;
  while (Wire.available()) { // slave may send less than requested   
    confirm[d] = Wire.read(); // receive a byte as character
    d++;
  }
  confirm[d] = 0;
  return atoi(confirm);
}



void sendvSetting(){
  Wire.beginTransmission(slaveAddress);
  vTransmit =vSetting * pMod;
  Wire.write(vTransmit);
  Serial.print("s");
  Serial.print(vSetting);
  Serial.print(", ");
  Wire.endTransmission();
  lineCounter = lineCounter + 1;

 }

void monitorVSetting(){
  vReading = confirmVSetting()/pMod ;
  
  Serial.print("r");
  Serial.print(vReading);
  Serial.print(", ");


}



void runLineCounter(){
    if (lineCounter >7) {
    lineBreak(1);
    lineCounter = 0;
    
  }
}

void loop() {

  if (Serial.available() > 0) {
  int d = 0;
  lineCounter = 0;
  while (Serial.available()) { // slave may send less than requested   
    vSettingNewChar[d] = Serial.read(); // receive a byte as character
    d++;
  }
  vSettingNewChar[d] = 0;
  
  vSettingNew = atoi(vSettingNewChar);            // Convert input to number
  lineBreak(2); 
  Serial.print("Input: ");
  Serial.print(vSettingNewChar);
  if (vSettingNew <= vMax && vSettingNew >= vMin){ // Check input is within pressure setting range
    vSetting = vSettingNew;
    lineBreak(1);
    Serial.print("New pulse setting entered. Pressure setting ");
    Serial.print(vSetting);
    Serial.println(" to send to controller");
    lineBreak(1);
    } else {
    lineBreak(1);
    Serial.print("Invalid input! Please use an input between ");
    Serial.print(vMin);
    Serial.print(" and ");
    Serial.print(vMax);
    lineBreak(1);  lineBreak(2);
    }
  }
    monitorVSetting();
  delay(loopTiming);
    sendvSetting();
    runLineCounter();
  }


 

void lineBreak(int f){
      for(int i = 0; i < f; i++)
    {
    Serial.println(" ");
    }
}

