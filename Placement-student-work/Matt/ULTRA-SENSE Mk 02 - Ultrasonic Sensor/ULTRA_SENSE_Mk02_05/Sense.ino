Sense::Sense(int trig, int ech, Buzz* b, Sense* n, int num)
{
    trigger = trig;
    echo = ech;
    buzzer = b;
    next = n;
    sensorNumber = num;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trigger, 0);
    eHigh = false;
    lastDistance = LONG_DISTANCE;
    previousDistance = LONG_DISTANCE;
    trigTime = micros();
}

Buzz* Sense::Buzzer()
{
  return buzzer;
}

Sense* Sense::Next()
{
  return next;
}

int Sense::SensorNumber()
{
  return sensorNumber;
}

void Sense::PrintState()
{
  Serial.print("Sensor: "); Serial.print(SensorNumber()); Serial.print(": ");
  if(lastDistance < 0) {
    Serial.println("[BUSY - READING]");
    } else {
    Serial.print("dist: ");
    Serial.print(lastDistance);
    Serial.print("cm, pulse: ");
    Serial.print(buzzer->GetDuration());
    Serial.print("ms, gap: ");
    Serial.print(buzzer->GetGap());
    Serial.print("ms, intensity: ");
    Serial.print(buzzer->GetIntensity());
    Serial.println("PWM");  
    }
}





void Sense::SetNext(Sense* n)
{
  next = n;
}

float Sense::TimeToDistance(long t)
{
  return (float)t/SOUND_TIME;
}

bool Sense::TimeOut()
{
  if(lastDistance >= 0)
    return false;

  long tim = micros() - trigTime; 
  if(TimeToDistance(tim) > LONG_DISTANCE*2.0)
    return true;
  return false;
}

void Sense::Reset()
{
   lastDistance = previousDistance;
}
    
void Sense::Spin()
{
  buzzer->Spin();
  
  if(lastDistance >= 0)
    return;

  int e = digitalRead(echo);
  if(e)
  {
    eHigh = true;
  } else
  {
    if(eHigh)
    {
      long tim = micros() - trigTime;
      lastDistance = TimeToDistance(tim);
      eHigh = false;
    }
  }
}


float Sense::Distance()
{
  return lastDistance;
}

void Sense::Trigger()
{
  if(lastDistance < 0)
    return;
    
  trigTime = micros();
  digitalWrite(trigger, 1);
  delayMicroseconds(10);
  digitalWrite(trigger, 0);
  previousDistance = lastDistance;
  lastDistance = -1.0;
  eHigh = false;
}

