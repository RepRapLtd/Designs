/* 
 *  
 */

//const int ledPin =  -1; 
const int aPin = 0;
const int bPin = 4;
//const int aSense = 2;
//const int bSense = 3;
//const int dir = 4;
const int pwm = 160;

void stop()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  //if(ledPin >= 0) digitalWrite(ledPin, 0);
}

void toA()
{
  /*if(!digitalRead(aSense))
  {
    stop();
    return;
  }*/
  digitalWrite(bPin, 0);
  analogWrite(aPin, pwm);
  //if(ledPin >= 0) digitalWrite(ledPin, 1);
}

void toB()
{
  /*if(!digitalRead(bSense))
  {
    stop();
    return;
  }*/
  digitalWrite(aPin, 0);
  analogWrite(bPin, pwm);
  //digitalWrite(ledPin, 1);
}

void setup() 
{
  //if(ledPin >= 0) pinMode(ledPin, OUTPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  //pinMode(aSense, INPUT);
  //digitalWrite(aSense,1);  
  //pinMode(bSense, INPUT);
  //digitalWrite(bSense,1);
  //pinMode(dir, INPUT);
  //digitalWrite(dir,1);  
  //Serial.begin(115200);
}


void loop() 
{
  if((millis()/1000)%2)
    toA();
  else
    toB();
}

