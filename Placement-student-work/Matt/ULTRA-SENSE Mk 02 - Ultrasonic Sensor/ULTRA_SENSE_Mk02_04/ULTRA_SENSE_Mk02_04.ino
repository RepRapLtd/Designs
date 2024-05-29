int counter = 0;
int ping;
int pwmNorth = 0;
int intDistance;
int pinRead;
int pinTrigger;
int pinPWM;
int currentSensor = 1;
int intPWM;


#define modNo               5
#define maxRange            300
#define noOfSensors         3
#define pinLED              13



void setup() {
  Serial.begin(9600);
  Serial.println("Set-up beginning");
  currentSensor = 1;
  while (currentSensor <= noOfSensors){
    pinTrigger = pinTriggerSet();
    pinPWM = pinPWMSet();
    pinRead = pinReadSet();
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinPWM, OUTPUT);
    pinMode(pinRead, INPUT);
    currentSensor++;
    }
 
  digitalWrite(pinTrigger, LOW);
  Serial.println("Set-up finished");
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
  currentSensor = 1;
  while (currentSensor <= noOfSensors){
    intDistance = distance();
    Serial.print("  Pin "); Serial.print(currentSensor); Serial.print(": ");
    Serial.print(intDistance);
    /*intPWM = 255/sqrt(intDistance/modNo);
    if (intPWM > 255){intPWM = 255;}
    if (intDistance > maxRange) {intPWM = 0;}
    analogWrite(pinPWM, intPWM);*/
    currentSensor++;
  }
  Serial.println(".");

  }




float distance(){
    pinTrigger = pinTriggerSet;
    pinPWM = pinPWMSet();
    pinRead = pinReadSet();
    
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);
 
   while (digitalRead(pinRead)==LOW){delayMicroseconds(1);}
  while (digitalRead(pinRead)){
    counter++; 
    delayMicroseconds(57);
    }
    ping = counter;
    counter = 0;
    return ping;
  }


int pinPWMSet(){
    int p;
    if(currentSensor>2) {p = currentSensor + 6;} else {p = currentSensor + 4;} 
    return p;
  }

int pinTriggerSet(){
    int t;
    t = currentSensor + 1;
    return t;
  }

int pinReadSet(){
    int r;
    r = currentSensor + 13;
    return r;
  }

