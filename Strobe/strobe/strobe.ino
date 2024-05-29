/* 
 *  
 */

const int ledPin =  13;      // the number of the LED pin

unsigned long previousMicros = 0;
unsigned long oldMicros = 0;
unsigned long offMicros = 0;
unsigned long currentMicros = 0;



const int loopTime = 360;
const float topF = 2000.0;
const float topA = 1023.0;
const float k = log(topF)/topA;
const float z = topF + 1.0;

float f = 1.0;

long interval = 1000;

long count = 0;

long del = 10000;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

inline void off()
{
   digitalWrite(ledPin, LOW);  
}


inline void on()
{
   digitalWrite(ledPin, HIGH);
   offMicros = currentMicros + del;
}

void loop() 
{
  currentMicros = micros();

  if (currentMicros - previousMicros >= interval) 
  {
    // save the last time you blinked the LED
    previousMicros = currentMicros;
    on();   
  }

  if(currentMicros - offMicros >= 0)
  {
    off();
  }
   
  count++;
  if(count > 1000)
  {
    count = 0;
    Serial.print("Frequency: ");
    Serial.print(f);
    Serial.print(" Hz.  Loop time: ");
    Serial.print(currentMicros - oldMicros);
    Serial.println(" microseconds.");
  }

  f = z - exp(k*(float)analogRead(0));
  interval = (long)(1000000.0/f);
  if(interval < del)
    del = interval/2;
  else
    del = 10000;
  oldMicros = currentMicros;
}

