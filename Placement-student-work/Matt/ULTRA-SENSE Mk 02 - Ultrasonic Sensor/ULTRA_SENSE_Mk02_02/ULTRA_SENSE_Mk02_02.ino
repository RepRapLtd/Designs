int counter = 0;
bool countOn = true;
int ping;
int pwmNorth = 0;
int intDistance;


#define modNo               5
#define pinBuzzNorth        3
#define pinTriggerNorth     A0
#define pinReadNorth        A1
#define maxRange            300



void setup() {
  pinMode(pinTriggerNorth, OUTPUT);
  pinMode(pinReadNorth, INPUT);
  Serial.begin(9600);
  digitalWrite(pinTriggerNorth, LOW);

  }


void loop() {
  intDistance = distance();
  pwmNorth = 255/sqrt(intDistance/modNo);
  if (pwmNorth > 255){pwmNorth = 255;}
  if (intDistance > maxRange) {pwmNorth = 0;}
  analogWrite(pinBuzzNorth, pwmNorth);
  Serial.print(pwmNorth);
  Serial.print("PWM, ");
  Serial.print(distance());
  Serial.println("cm");
}




float distance(){
  digitalWrite(pinTriggerNorth, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTriggerNorth, LOW);
  countOn = true;
  while (digitalRead(pinReadNorth)==LOW){delayMicroseconds(1);}
  while (digitalRead(pinReadNorth)){
    counter++; 
    delayMicroseconds(57);
    }
    ping = counter;
    counter = 0;
    return ping;
  }

