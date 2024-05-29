#ifndef BUZZ_H
#define BUZZ_H

class Buzz
{
  public:
  
    Buzz(int pinNumber);
    void Spin();
    void SetDuration(long msecs);
    void SetGap(long msecs);
    void SetIntensity(int i);
    long GetDuration();
    long GetGap();
    int GetIntensity();

  private:

    int pin;
    long duration;
    long gap;
    int intensity;
    long nextOn;
    long nextOff;
};

#endif


