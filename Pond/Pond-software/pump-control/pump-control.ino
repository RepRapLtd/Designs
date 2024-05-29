

#define LEDPIN 13
#define VOLTPIN 5
#define PUMPPIN 2
#define DEBUGPIN 12
float voltage;

bool debug = true;

const float factor = (12.04/579.0);
const float minV = 11.0;
const float maxV = 12.0;

void setup() 
{
  pinMode(LEDPIN, OUTPUT);
  pinMode(PUMPPIN, OUTPUT);
  pinMode(DEBUGPIN, INPUT_PULLUP);
  digitalWrite(LEDPIN, 0);
  digitalWrite(PUMPPIN, 0);
  debug = !digitalRead(DEBUGPIN);
  if(debug)
  {
    Serial.begin(9600);
  }
}

void On()
{
  digitalWrite(PUMPPIN, 1);  
  digitalWrite(LEDPIN, 1);    
}

void Off()
{
  digitalWrite(PUMPPIN, 0);  
  digitalWrite(LEDPIN, 0);    
}

void loop() 
{
  voltage = factor*(float)analogRead(VOLTPIN);
  if(debug)
  {
    Serial.println(voltage);
  }
  if(voltage < minV)
    Off();
  if(voltage > maxV)
    On();
    
// NB - short cycle time wastes energy on siphon-back.

  if(debug)
  {
    delay(1000L);
  } else
  {
    delay(60000L);
  }
  
}
