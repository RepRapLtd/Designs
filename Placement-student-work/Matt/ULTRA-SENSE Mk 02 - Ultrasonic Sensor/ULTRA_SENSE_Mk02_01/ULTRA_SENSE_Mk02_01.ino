int counter = 0;
bool countOn = true;
int ping;
int oldDistance;
int newDistance;


#define tolerance     20
#define pinTrigger    3
#define pinRead       2
#define pinLED        13


void setup() {
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinRead, INPUT);
  Serial.begin(9600);
  digitalWrite(pinTrigger, LOW);
  digitalWrite(pinLED, LOW);
  }


void loop() {
  newDistance = distance();
   // if (newDistance > oldDistance + tolerance or newDistance < oldDistance - tolerance){
        Serial.println(newDistance);
       /* }
       oldDistance = newDistance;
    */
    
delay(1000);
}




int distance(){
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
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

