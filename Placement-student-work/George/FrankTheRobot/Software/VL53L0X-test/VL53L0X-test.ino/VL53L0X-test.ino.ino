/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

float rateLimit = 0.25;
uint32_t timingBudget = 100000;
uint8_t periodPrePclks = 18; // Must be even
uint8_t periodFinalPclks = 14; // Must be even

VL53L0X sensor;

void StartSensor()
{
  Serial.println("Sensor starting.");
  
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);
  if(!sensor.setSignalRateLimit(rateLimit))
  {
    Serial.println("Rate limit out of range.");
    sensor.setSignalRateLimit(0.25);
  }

  if(!sensor.setMeasurementTimingBudget(timingBudget))
  {
    Serial.println("Timing budget out of range.");
    sensor.setMeasurementTimingBudget(33000);
  }

  if(!sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, periodPrePclks))
  {
    Serial.println("Pulse pre period wrong.");
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);
  }

  if(!sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, periodFinalPclks))
  {
    Serial.println("Pulse final period wrong.");
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10);
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();  
}

unsigned int lastDistance = 0;

unsigned int distance()
{
  unsigned int r = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) { Serial.println("\nSensor timeout"); }
  if(r > 7500)
  {
    if(r > 9000)
      Serial.println("Sensor reset needed.");
    r = lastDistance;
  } else
    lastDistance = r;
  return r;
}

void setup()
{
  Serial.begin(9600);
  StartSensor();
}

int loopCount = 0;

void loop()
{
  if(loopCount > 20)
  {
    while(Serial.available() <= 0);
    int c = Serial.read();
    loopCount = 0;
  }
  Serial.println(distance());
  loopCount++;
}
