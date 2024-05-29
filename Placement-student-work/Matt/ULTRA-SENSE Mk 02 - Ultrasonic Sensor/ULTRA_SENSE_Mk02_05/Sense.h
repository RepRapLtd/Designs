#ifndef SENSE_H
#define SENSE_H

#define SOUND_TIME 57.0
#define LONG_DISTANCE 300.0

class Sense
{
  public:
  
    Sense(int trig, int ech, Buzz* b, Sense* n, int num);
    void Spin();
    float Distance();
    void Trigger();
    bool TimeOut();
    void Reset();
    Buzz* Buzzer();
    Sense* Next();
    void SetNext(Sense* n);
    void PrintState();
    int SensorNumber();

  private:

    float TimeToDistance(long t);
    int trigger;
    int echo;  
    int sensorNumber;
    long trigTime;
    //bool active;
    bool eHigh;
    float lastDistance;
    float previousDistance;
    Buzz* buzzer;
    Sense* next;
};

#endif
