  

  #define pinMeasure A0
  #define pinOutput 13
  #define frequencyMod 0.0015

  long frequencyDelay;
  int frequencyModMove;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinMeasure, INPUT);
  pinMode(pinOutput, OUTPUT);
  frequencyModMove = 1;

}

void loop() {

frequencyDelay = (analogRead(pinMeasure)/100) * (analogRead(pinMeasure)/100)* (analogRead(pinMeasure)/100)* (analogRead(pinMeasure)/100);
//if(frequencyDelay >3000) {
  
    digitalWrite(pinOutput, HIGH);
    delayMicroseconds(frequencyDelay * frequencyMod);
    digitalWrite(pinOutput, LOW);
    delayMicroseconds(frequencyDelay * frequencyMod);
  //Serial.println(500000/(frequencyDelay * frequencyMod));
  Serial.println(frequencyDelay);
  //}
}
