  
  int distance;
  int newDistance;
  int counter;
  #define distanceMod 3
  #define distanceModAdd 320
  #define tolerance 3
  #define baseline 45
  #define pinMeasure A0
  #define pinOutput 13
  #define buzzerFrequency 18  //Hz
  int frequencyDelay;
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinMeasure, INPUT);
  pinMode(pinOutput, OUTPUT);

}

void loop() {
  /* newDistance = analogRead(A0) * distanceMod;
  if (newDistance > distance + tolerance or newDistance < distance - tolerance){
    distance = newDistance;
    if (distance < baseline){Serial.println(">40cm");} else {
      Serial.println(distance);
      }
    }*/
  newDistance = (distanceModAdd - analogRead(pinMeasure)) / distanceMod;
  if (newDistance > distance + tolerance or newDistance < distance - tolerance){
    distance = newDistance;
    if (distance > baseline){Serial.print(">"); Serial.print(baseline); Serial.println("cm");} else {
      Serial.print(distance); Serial.println("cm");
      counter = 1;
      frequencyDelay = 500000/buzzerFrequency;
      while(counter < buzzerFrequency) {
        counter++;
        if(frequencyDelay > 1) {frequencyDelay --;} else {frequencyDelay = 500000/buzzerFrequency;}
        digitalWrite(pinOutput, HIGH);
        delayMicroseconds(frequencyDelay);
        digitalWrite(pinOutput, LOW);
        delayMicroseconds(frequencyDelay);
        }
      }
    }
  delay(100);
}
