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

int stepTimer = 500;     // Define the variable that controls the blink length
char vSettingNewChar[7];
int vSettingNew;
int pinPower = 3;
int pinLED = 13;
double voltage = 0;



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);  // start serial for output
  pinMode(pinPower, OUTPUT);
  pinMode(pinLED, OUTPUT);
  Serial.println("Enter PWM");
  setPwmFrequency(pinPower, 1);

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
  delay(stepTimer);              // wait for the specified time
  digitalWrite(pinLED, HIGH);
  delay(50);
  digitalWrite(pinLED, LOW);


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
