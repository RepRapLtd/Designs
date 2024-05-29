Buzz::Buzz(int pinNumber)
{
  pin = pinNumber;
  pinMode(pin, OUTPUT);
  analogWrite(pin, 0);
  duration = 200;
  gap = 1000;
  intensity = 255;
  nextOn = millis() + gap + duration;
  nextOff = nextOn + duration;
}

void Buzz::Spin()
{
  long now = millis();

  if(now - nextOn >= 0)
  {
    analogWrite(pin, intensity);
    nextOn = now + duration + gap;
    nextOff = now + duration;
  }

  if(now - nextOff >= 0)
  {
    analogWrite(pin, 0);
    //nextOff = nextOn + duration;
  }  
}

void Buzz::SetDuration(long msecs)
{
  duration = msecs;
}

void Buzz::SetGap(long msecs)
{
  gap = msecs;
}

void Buzz::SetIntensity(int i)
{
  if(i > 255)
    i = 255;
  intensity = i;
}

long Buzz::GetDuration()
{
  return duration;
}


long Buzz::GetGap()
{
  return gap;
}

int Buzz::GetIntensity()
{
  return intensity;
}

