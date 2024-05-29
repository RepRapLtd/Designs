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
const int stepTimer = 15;      // Define the variable that controls the step length
const int maxVoltage = 500;     // Set a maximum allowable voltage (max possible value is 255 x voltageMod)
const int minVoltage = 10;      // Set a minimum voltage (lower numbers than this are used for commands)
const double voltageMod = 2.67; // Divisor to convert mV into PWM


const int pinStep = 13;         // Pin driving STEP on the chip
const int pinDirection = 12;    // Pin driving DIR on the chip
const int pinPower = 3;         // Pin driving REF on the chip

char vSettingNewChar[7];        // Serial input
int vSettingNew;                // Serial input as integer
bool stepping = false;          // Step on/off
bool stepForward = true;        // Dir forwards/backwards
int voltage = 0;                // REF voltage




// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

  Serial.begin(9600);                           // start serial for output
  pinMode(pinStep, OUTPUT);                     // Set up pins
  pinMode(pinPower, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  userInstructions();                           // User instructions

}


void userInstructions(){
  Serial.println("[] 1 for step to start/stop");   
  Serial.println("[] 2 to change direction");
  Serial.print("[] 0 or >=");
  Serial.print(minVoltage);
  Serial.print(" and <=");
  Serial.print(maxVoltage);
  Serial.print(" to set ref voltage in mV (Max possible circuit power is ");
  int circuitMax = voltageMod * 255;
  Serial.print(circuitMax);
  Serial.println("mV)");
}
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

// the loop function runs over and over again forever
void loop() {
  inputCheck();
  runStep();
}


void runStep() {
  analogWrite(pinPower, voltage);
    if (stepForward == true) {digitalWrite(pinDirection, HIGH); } else{digitalWrite(pinDirection, LOW); } 
    if (stepping == true) {           // Check if stepping is ON
      digitalWrite(pinStep, HIGH);    // turn the motor on (HIGH is the voltage level)
      delay(stepTimer/2);             // wait for the specified time
      digitalWrite(pinStep, LOW);     // turn the motor off (LOW is the voltage level)
      delay(stepTimer/2);             // wait for the specified time
    }
    else
    {delay(stepTimer);}


}

void inputCheck() {

  if (Serial.available() > 0) {
    int d = 0;
    while (Serial.available()) { // slave may send less than requested
      vSettingNewChar[d] = Serial.read(); // receive a byte as character
      d++;
    }
    vSettingNewChar[d] = 0;

    vSettingNew = atoi(vSettingNewChar);
    if (vSettingNew > maxVoltage) {                                   // Check voltage is within set limits
      Serial.print("Too High! Enter a voltage equal to or below ");   // Inform user is voltage is not allowed
      Serial.print(maxVoltage);
      Serial.println("mV.");
      voltage = 0;
    } else {
      if(vSettingNew >= minVoltage) {                                 // Check if value entered is a voltage or a code
      voltage = vSettingNew/voltageMod;                               // Convert voltage to PWM
      Serial.print(vSettingNew);                                      // Confirm to user that voltage has been entered
      Serial.println("mV");
      }
      else{inputCodes();}                                             // If not a voltage, go to codes module
    }
  }

}


void inputCodes(){
          Serial.print(" - ");
          Serial.print(vSettingNew);
          if( vSettingNew ==0) {voltage = 0; Serial.println("mV");}   // Set REF to 0
          if (vSettingNew == 1) {if(stepping == true){stepping = false;Serial.println(" Stop");} else {stepping = true;Serial.println(" Start");}}
            // ^ switch from START to STOP
          if (vSettingNew == 2) {if(stepForward == true){stepForward = false;Serial.println(" Back");} else {stepForward = true;Serial.println(" Forward");}}
            // ^ switch from FORWARD to BACK
          if (vSettingNew >= 3) {Serial.println(" Invalid input");}
            // ^ inform the user if a not-yet assigned code has been entered
          vSettingNew = 0;    // Reset the variable to 0 after the module has finished
          
}

