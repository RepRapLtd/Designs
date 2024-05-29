int counter = 0;
bool countOn = true;
int ping;
int pwmNorth = 0;
int intDistance;
int pinNumber = 0;


#define modNo               5
#define pinBuzzNorth        3
#define pinTriggerNorth     A5
#define pinTriggerWest      A4
#define pinTriggerEast      A3
#define pinRead             A0
#define maxRange            300



void setup() {
  pinMode(pinTriggerNorth, OUTPUT);
  pinMode(pinTriggerWest, OUTPUT);
  pinMode(pinTriggerEast, OUTPUT);
  pinMode(pinRead, INPUT);
  Serial.begin(9600);
  digitalWrite(pinTriggerNorth, LOW);
  digitalWrite(pinTriggerWest, LOW);
  digitalWrite(pinTriggerEast, LOW);
  }


void loop() {
  /*intDistance = distance();
  pwmNorth = 255/sqrt(intDistance/modNo);
  if (pwmNorth > 255){pwmNorth = 255;}
  if (intDistance > maxRange) {pwmNorth = 0;}
  analogWrite(pinBuzzNorth, pwmNorth);
  Serial.print(pwmNorth);
  Serial.print("PWM, ");
  Serial.print(distance());
  Serial.println("cm");*/
  pinNumber = 1;
  while (pinNumber < 4){
    pinNumber++;
    intDistance = distance();
    if(pinNumber = 1) {Serial.print("North: ");} else if(pinNumber = 2) {Serial.print("West: ");} else  {Serial.print("East: ");} 
    Serial.print(intDistance);
  }
  Serial.println(".");

  }




float distance(){
  if (pinNumber == 1) {
    digitalWrite(pinTriggerNorth, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTriggerNorth, LOW);
    }
  else if (pinNumber == 2) {
    digitalWrite(pinTriggerWest, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTriggerWest, LOW);
    }
  else {
    digitalWrite(pinTriggerEast, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTriggerEast, LOW);
    }
   
  countOn = true;
  while (digitalRead(pinRead)==LOW){delayMicroseconds(1);}
  while (digitalRead(pinRead)){
    counter++; 
    delayMicroseconds(57);
    }
    ping = counter;
    counter = 0;
    return ping;
  }

