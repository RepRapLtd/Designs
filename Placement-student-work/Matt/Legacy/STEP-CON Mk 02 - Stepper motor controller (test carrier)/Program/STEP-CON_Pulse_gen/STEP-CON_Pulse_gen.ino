//RepRap Ltd Pressure Controller

/*
#include <Wire.h>
#include<stdio.h>
#include<stdlib.h>
#include <TimeLib.h>
#include <string.h>

*/

/*I2C Address of the controller */

int loopTiming = 5;
int pinClock = 13;
int pinDIR = 12;
char pSettingNewChar[7];

void setup() {
  pinMode(pinClock, OUTPUT);
  pinMode(pinDIR, OUTPUT);
  digitalWrite(pinDIR, HIGH);
  Serial.begin(115200);
  showFreq();
}


void showFreq(){
          Serial.print(loopTiming);
          Serial.println("Hz");
}


void pulse(){
  digitalWrite(pinClock, HIGH);
  delay(500/loopTiming);
  digitalWrite(pinClock, LOW);
  delay(500/loopTiming);
  
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



