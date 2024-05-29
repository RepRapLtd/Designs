/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

int stepTimer = 100;      // Define the variable that controls the blink length
char sSettingNewChar[7];
int sSettingNew;
bool stepping = false;
bool stepForward = true;
int pinStep = 13;
int pinDirection = 12;
char vSettingNewChar[7];
int vSettingNew;
int pinPower = 3;
int pinLED = 13;
double voltage = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);  // start serial for output
  pinMode(pinStep, OUTPUT);
  pinMode(pinPower, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  Serial.println("1 for step to begin");
  Serial.println("2 for step to stop");
  Serial.println("3 to change direction");
  Serial.println("4 to change ref voltage");
  analogWrite(pinPower, voltage);
}



// the loop function runs over and over again forever
void loop() {
    inputCheck();
  runStep();
  }


void runStep(){
    if (stepForward == true) {digitalWrite(pinDirection, HIGH); } else{digitalWrite(pinDirection, LOW); } 
    if (stepping == true) {
      digitalWrite(pinStep, HIGH);         // turn the LED on (HIGH is the voltage level)
      delay(stepTimer);              // wait for the specified time
      digitalWrite(pinStep, LOW);         // turn the LED on (HIGH is the voltage level)
      delay(stepTimer);              // wait for the specified time
    }
    
}

void inputCheck(){

    if (Serial.available() > 0) {
  int d = 0;
  while (Serial.available()) { // slave may send less than requested   
    sSettingNewChar[d] = Serial.read(); // receive a byte as character
    d++;
  }
  sSettingNewChar[d] = 0;
    
    sSettingNew = atoi(sSettingNewChar);
    if( sSettingNew ==0) {} else {Serial.print(sSettingNew);}
    if (sSettingNew == 1) {stepping = true; Serial.println(" Step");}
    if (sSettingNew == 2) {stepping = false; Serial.println(" Stop");}
    if (sSettingNew == 3) {if(stepForward == true){stepForward = false;Serial.println(" Back");} else {stepForward = true;Serial.println(" Forward");}}
    if (sSettingNew == 4) {inputVoltage();}
    sSettingNew = 0;
  }
}


void inputVoltage(){

  if (Serial.available() > 0) {
    int d = 0;
    while (Serial.available()) { // slave may send less than requested
      vSettingNewChar[d] = Serial.read(); // receive a byte as character
      d++;
    }
    vSettingNewChar[d] = 0;

    vSettingNew = atoi(vSettingNewChar);
    if (vSettingNew > 255) {
      Serial.println("Too High!");
      voltage = 0;
    } else {
      voltage = vSettingNew;
      Serial.print(vSettingNew);
      Serial.println("PWM");
    }
  }
}
