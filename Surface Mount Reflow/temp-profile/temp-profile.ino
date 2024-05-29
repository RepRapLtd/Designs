/*

  Toaster Oven SMT soldering control
  
  Adrian Bowyer
  
  2 November 2011
  
  Licence: GPL
  
*/

#define THERMISTOR_BETA 4200 // thermistor: RS 538-0806
#define THERMISTOR_SERIES_R 4590 // Ohms in series with the thermistors
#define THERMISTOR_25_R 100000.0 // Thermistor ohms at 25 C = 298.15 K
#define AD_RANGE 1023.0 // The A->D converter that measures temperatures gives an int this big as its max
#define ABS_ZERO -273.15  // Celsius

const int heatPin =  13;     // the number of the LED pin.  This also controls the heater
int heatState = LOW;         // heatState used to set the LED and heater
long previousMillis = 0;     // will store last time LED/heater was updated
const long interval = 1000;  // interval at which to sample temperature (milliseconds)
const int tempPin = 0;       // Analogue pin for temperature reading
long time = 0;               // Time since start in seconds
bool done=false;             // Flag to indicate that the process has finished
bool thermocouple=false;     // Switch thermocouple thermistor
int constTemp = -300;

// The temperature/time profile as {secs, temp}
// This profile is linearly interpolated to get the required temperature at any time.
// PLEN is the number of entries
#define PLEN 7
long profile[PLEN][2] = { {0, 15}, {120, 150}, {220, 183}, {280, 215}, {320, 215}, {340, 183}, {380, 0} };

// Linearly interpolate the profile for the current time in secs, t, or
// return the constant temperature, as appropriate.

int target(long t)
{
  if(constTemp > -273)
  {
    return constTemp;
  }
  
  if(t <= profile[0][0])
   return profile[0][1];
  if(t >= profile[PLEN-1][0])
  {
   done = true; // We are off the end of the time curve
   return profile[PLEN-1][1];
  }
  for(int i = 1; i < PLEN-1; i++)
  {
     if(t <= profile[i][0])
       return (int)(profile[i-1][1] + ((t - profile[i-1][0])*(profile[i][1] - profile[i-1][1]))/
         (profile[i][0] - profile[i-1][0]));
  }
  return 0;
}

// Measure the temperature from the thermocouple

int thermocoupleTemperature()
{
  return (int)( 5.0 * analogRead(tempPin) * 100.0) / 1024.0;
}

int thermistorTemperature()
{
  float r = (float)analogRead(tempPin);
  return ABS_ZERO + THERMISTOR_BETA/log( (r*THERMISTOR_SERIES_R/(AD_RANGE - r))/
      ( THERMISTOR_25_R*exp(-THERMISTOR_BETA/(25.0 - ABS_ZERO)) ) );
}

int temperature()
{
  if(thermocouple)
    return thermocoupleTemperature();
  else
    return thermistorTemperature();
}

// Get the show on the road

void setup() {

  pinMode(heatPin, OUTPUT); 
  pinMode(tempPin, INPUT);  
  Serial.begin(9600);
  bool set = false;
  while(!set)
  {
    Serial.println("\n\nType P to follow the profile or T nn to set to nn degrees C:");
    while(Serial.available() <= 0);
    int c = Serial.read();
    if(c == 'P')
    {
      set = true;
      constTemp = -300;
    } else if (c == 'T')
    {
      constTemp = Serial.parseInt();
      set = true;
    }
  }
  Serial.println("\n\n\nTime, target, temp"); 
  done = false;
}

// Go round and round

void loop()
{
  int t;
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) 
  {
    previousMillis = currentMillis; // set next time 
    
    // Get the actual temperature
    
    t = temperature();
    
    // One second has passed
    
    time++;   
    
    // Find the target temperature
    
    int tg = target(time);
    
    // Simple bang-bang temperature control
    
    if (t < tg)
    {
      heatState = HIGH;
    } else
    {
      heatState = LOW;
    }

    // Turn the heater on or off (and the LED)
    digitalWrite(heatPin, heatState);
    
    // Keep the user amused
    if(done)
    {
      Serial.print((char)0x07);  // Bell to wake the user up...
      Serial.print((char)0x07);
      Serial.print("FINISHED ");
    }
    Serial.print(time);
    Serial.print(", ");
    Serial.print(tg);
    Serial.print(", ");
    Serial.println(t);
  }
}
