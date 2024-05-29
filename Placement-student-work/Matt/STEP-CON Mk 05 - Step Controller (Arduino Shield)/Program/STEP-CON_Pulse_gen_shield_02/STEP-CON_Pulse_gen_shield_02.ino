//RepRap Ltd Pressure Controller

/*
#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>
#include <string.h>

*/

/*I2C Address of the controller */

int loopTiming = 100;
int pinSTEP = A1;
int pinDIR = A0;
int pinREF = 3;
int pinClock = 2;
int pinPulse =  13;


char pSettingNewChar[7];

void setup() {
  pinMode(pinPulse, OUTPUT);
  pinMode(pinDIR, OUTPUT);
  pinMode(pinREF, OUTPUT);
  pinMode(pinClock, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinClock), stepRunFunction, FALLING);
  showFreq();
  analogWrite(pinREF, 60);
  digitalWrite(pinDIR, HIGH);
  sei();
}

void stepRunFunction(){
    //if(stepRun == true) {
      digitalWrite(pinSTEP, LOW);
      delay(1);
      digitalWrite(pinSTEP, HIGH);
    //}
    
}

void showFreq(){
          Serial.print(loopTiming);
          Serial.println("Hz");
}


void pulse(){
  //digitalWrite(pinSTEP, HIGH);
  delay(500/loopTiming);
  //digitalWrite(pinSTEP, LOW);
  delay(500/loopTiming);
  stepRunFunction();
  
 if (Serial.available() > 0) {
          int d = 0;
              while (Serial.available()) { // slave may send less than requested   
              pSettingNewChar[d] = Serial.read(); // receive a byte as character
              d++;
              }
          loopTiming= atoi(pSettingNewChar);
          showFreq();
          d=0;
          }
}

void loop() {
  pulse();
  
  }



