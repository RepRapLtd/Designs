/*
 * Test program for Frank The Robot
 * 
 * This allows all the electronic and mechanical functions to
 * be run and tested individually.
 * 
 * Adrian Bowyer
 * RepRap Ltd
 * http://reprapltd.com
 * 
 * 8 June 2018
 * 
 * Licence: GPL
 */
#include <ESP8266WiFi.h>

const char* ssid = "reprapltd";
const char* password = "1sgdttsa";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);


#include <Wire.h>
//#include <VL53L0X.h>

//VL53L0X sensor;

#define WEMOS_R2_BOARD

#ifdef WEMOS_R1_BOARD

// Wemos D1 R1 "Arduino" pins

const char rRIN = D6; // Right motor pins
const char rFIN = D5; //

const char lRIN = D8; // Left motor pins
const char lFIN = D7; //

const char rSense = D9; // Wheel sensors NB: LED pin - LED pulls up?
const char lSense = D10; // (Input pulldown)

const char led = LED_BUILTIN; // D9

const char aSelect = D2;     // Select analogue channel
const char aRead = A0;       // Read analogue voltage
#endif


#ifdef WEMOS_R2_BOARD
// Wemos D1 R2 "Arduino" pins

const char rRIN = D4; // Right motor pins
const char rFIN = D3;

const char lRIN = D6; // Left motor pins
const char lFIN = D8;

const char rSense = D7; // Wheel sensors
const char lSense = D5;

const char led = LED_BUILTIN;

const char aSelect = D0;     // Select analogue channel
const char aRead = A0;       // Read analogue voltage
#endif

#ifdef WEMOS_MINI_BOARD
// Wemos Mini "Arduino" pins

const char rRIN = D8; // Right motor pins
const char rFIN = D6;

const char lRIN = D4; // Left motor pins
const char lFIN = D3;

const char rSense = D7; // Wheel sensors
const char lSense = D5;

const char led = LED_BUILTIN;

const char aSelect = D0;     // Select analogue channel
const char aRead = A0;       // Read analogue voltage
#endif

const char photo = false;    // Send to aSelect to read the photosensor
const char voltage = !photo; // Send to aSelect to read the battery voltage

// Motor directions, stop and motor control data

const char stop = 0;
const char forward = 1;
const char backward = 2;
volatile char leftDirection, rightDirection; // What each motor is doing
unsigned char lfPWM, lbPWM, rfPWM, rbPWM;    // PWM to control each motor speed (forward != backward in general)
volatile long leftCount, rightCount; // Counts of the wheel opto-slots
volatile long leftTime, rightTime;  // milliseconds that the motor's been turning
volatile char lStop, rStop; // Flag for when a motor has just stopped
char lRemember, rRemember;

// LIDAR numbers

float rateLimit = 0.25;
uint32_t timingBudget = 100000;
uint8_t periodPrePclks = 18; // Must be even
uint8_t periodFinalPclks = 14; // Must be even
unsigned int defaultDistance = 2000;

 

void SetupLIDAR()
{
  /*Serial.println("Sensor starting.");
  
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
  sensor.startContinuous();*/  
}

// Return the distance in mm

unsigned int LIDARDistance()
{/*
  unsigned int r = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred())
  {
    Serial.println("\nSensor timeout");
  }
  if(r > 7500)
  {
    if(r > 9000)
      Serial.println("Sensor reset needed.");
    r = defaultDistance;
  }*/
  return 100;  
}

// Control the leftmotor

void LeftMotor(char direction)
{
 Serial.println("Moving Left")
   /* switch(direction)
  {
    case forward:
      digitalWrite(lRIN, LOW);
      analogWrite(lFIN, lfPWM);
      break;
           
    case backward:
      digitalWrite(lFIN, LOW);
      analogWrite(lRIN, lbPWM);
      break;
      
    case stop:
    default:
      digitalWrite(lRIN, HIGH);
      digitalWrite(lFIN, HIGH);
  }

  // Remember what we're doing

  leftDirection = direction*/;
}
// Control the right motor

void RightMotor(char direction)
{
  Serial.println("Moving Right")
  /*
  switch(direction)
  {
    case forward:
      digitalWrite(rRIN, LOW);
      analogWrite(rFIN, rfPWM);
      break;
           
    case backward:
      digitalWrite(rFIN, LOW);
      analogWrite(rRIN, rbPWM);
      break;
      
    case stop:
    default:
      digitalWrite(rRIN, HIGH);
      digitalWrite(rFIN, HIGH);
  }

  // Remember what we're doing
  
  rightDirection = direction*/;  
}


void PrintDistance()
{
  Serial.print("The LIDAR distance (mm): ");
  Serial.println(LIDARDistance());  
}

void PrintWheels()
{
  Serial.print("The left and right wheel sensors are ");
  Serial.print(digitalRead(lSense));
  Serial.print(", ");
  Serial.println(digitalRead(rSense));  
}

void PrintIllumination()
{
  digitalWrite(aSelect,photo);
  int v = analogRead(aRead);
  Serial.print("Checking Illumination voltage: ");
  Serial.println(v);  
}

void PrintBattery()
{
  digitalWrite(aSelect,voltage);
  int v = analogRead(aRead);
  Serial.print("Checking battery voltage: ");
  Serial.println(v);  
}

// Set the right motor running for n opto-wheel-slot pulses

void RunRight(long n, char dir)
{
  Serial.println("Moving Right")
/*
  rightCount = n;
  RightMotor(dir);
  rightTime = millis()*/;
}

// Set the left motor running for n opto-wheel-slot pulses

void RunLeft(long n, char dir)
{
  Serial.println("Moving Left");
/*
  leftCount = n;
  LeftMotor(dir);
  leftTime = millis();
  */
}

// This function gets called by the interrupt on the falling edge
// of the left wheel opto-slot sensor signal.

void LeftInterupt()
{
  /*
  if(leftDirection == stop)
    return;
  leftCount--; // Countdown
  if(leftCount > 0)
    return;
  LeftMotor(stop);
  leftTime = millis() - leftTime;
  lStop = true;
  */
}


// This function gets called by the interrupt on the falling edge
// of the right wheel opto-slot sensor signal.

void RightInterupt()
{
/*
  if(rightDirection == stop)
    return;
  rightCount--; // Countdown
  if(rightCount > 0)
    return;
  RightMotor(stop);
  rightTime = millis() - rightTime;
  rStop = true;*/
}

// This gets called when the main loop detects that the left motor has stopped.

void LeftStopped()
{
  /*
  lStop = false;
  Serial.print("Turned Left");
  Serial.print(leftTime);
  Serial.println("");
  */
}

// This gets called when the main loop detects that the right motor has stopped.

void RightStopped()
{
  /*
  rStop = false;
  Serial.print("Turned Right");
  Serial.print(rightTime);
  Serial.println("");
  */
}

// Remind the user what can be done...

void Prompt()
{

  Serial.println("\nCommands:");
  Serial.println(" L n - turn left motor for n steps forward.");
  Serial.println(" l n - turn left motor for n steps backward.");
  Serial.println(" R n - turn right motor for n steps forward.");
  Serial.println(" r n - turn right motor for n steps backward.");
  Serial.println(" c - calibrate motor speeds.");
  Serial.println(" d - print distance reading.");
  Serial.println(" w - print states of wheel sensors.");
  Serial.println(" v - print battery voltage.");
  Serial.println(" i - print illumination voltage.");
  Serial.println(" g - reset PWMs to 255.");
  Serial.println();
  
}

void setup()
{
  
  Serial.begin(9600);
  Serial.println("begin");
  
  pinMode(rRIN, OUTPUT);
  pinMode(rFIN, OUTPUT);
  pinMode(lRIN, OUTPUT);
  pinMode(lFIN, OUTPUT);
  pinMode(rSense, INPUT_PULLUP);
  pinMode(lSense, INPUT_PULLUP);
  pinMode(aSelect, OUTPUT);
  pinMode(aRead, INPUT);

  RightMotor(stop);
  LeftMotor(stop);
 // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  attachInterrupt(digitalPinToInterrupt(rSense), RightInterupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(lSense), LeftInterupt, FALLING);
  
  SetupLIDAR();
 
  leftCount = 0;
  rightCount = 0;
  leftTime = 0;
  rightTime = 0;
  lStop = false;
  rStop = false;
  lfPWM = 255;
  lbPWM = 255;
  rfPWM = 255;
  rbPWM = 255;
  lRemember=false;
  rRemember=false;
  //Prompt();
  
  //Serial.print("Command: ");
    
}

void CalibrateMotorsSense()
{
  if(!lStop && !rStop)
    return;
    
  if (rStop&&!rRemember)
  {
    //rStop = false;
    rRemember=true;
    Serial.println("Testing Right Motor");
    Serial.print(rightTime);
    Serial.println("");
  }
  
  if (lStop&&!lRemember)
  {
    //lStop = false;
    lRemember=true;
    Serial.println("Testing Left Motor");
    Serial.print(leftTime);
    Serial.println("");
  }
  if(lStop && rStop)
  {
    lStop=false;
    rStop=false;
    if(leftTime > rightTime)
    {
      rfPWM = rfPWM * rightTime/leftTime;
    }else
    {
      lfPWM = lfPWM * leftTime/rightTime;
    }
    Serial.print("lfPWM = ");
    Serial.print(lfPWM);
    Serial.print(", rfPWM = ");
    Serial.println(rfPWM);
    rRemember=false;
    lRemember=false;
  }
}

void CalibrateMotors()
{
  RunRight(25,forward);
  
  RunLeft(25,forward);
}


void loop()
{
WiFiClient client = server.available();
  if (!client) 
  {
    CalibrateMotorsSense();
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nFrank is now "; 
  // Match the request

  if(req.indexOf("favicon")>=0)
  {
    req = "";
  }
/*  int val;
  if (req.indexOf("r/10") != -1)
  {  val = 0;
    s +="turning right.";
    digitalWrite(2, val);
  }else if (req.indexOf("/l/10") != -1)
   { val = 1;
    s +="turning left.";
    digitalWrite(2, val);
  }else {
    val=-1;
    s +="stationary.";
    //Serial.println("invalid request");
    //client.stop();
    //return;
  }
 */ 
  








  
  char c;
  long n;

  // Has the user typed a command?
  
  c = 0;
  //if (Serial.available() > 0) 
  //    c = (char)Serial.read();
  //if(c == '\n' || c == '\r' || c == ' ') // Throw away white space
  //  c = 0;

  // Pick c and maybe n out of String req here - 192.168.1.118/w  or /r/10
  int pos = req.indexOf("/");

  if(pos < 0)
  {
    c = 0;
  } else
  {
    c = req.charAt(pos+1);
  }
  String number;
  if(c)
  {
    Serial.println(c);
    
    switch(c)
    {
      case 'L':
        number = req.substring(pos+3);
        n = number.toInt();
        RunLeft(n, forward);
        break;
  
     case 'l':
        number = req.substring(pos+3);
        n = number.toInt();
        RunLeft(n, backward);
        break;
  
     case 'R':
        number = req.substring(pos+3);
        n = number.toInt();
        RunRight(n, forward);
        break;
  
     case 'r':
        number = req.substring(pos+3);
        n = number.toInt();
        RunRight(n, backward);
        break;

     case 'c':
        CalibrateMotors();
        break;
  
     case 'd':
        PrintDistance();
        break;
  
     case 'w':
        PrintWheels();
        break;
  
     case 'v':
        PrintBattery();
        break;
  
     case 'i':
        PrintIllumination();
        break; 
        
    case 'g':
        lfPWM = 255;
        lbPWM = 255;
        rfPWM = 255;
        rbPWM = 255;
        break;
  
      case 0:
        break;
  
      default:
        Serial.println("??");
        Prompt();
        break;
    }
    Serial.println("Done");
  }

  // Check if an interrupt function has stopped a motor and,
  // if so, report how long the motor turned.

  CalibrateMotorsSense();
  /*
  if(lStop)
  {
    LeftStopped();
    Serial.print("Command: ");
  }
    
  if(rStop)
  {
    RightStopped();
    Serial.print("Command: ");
  }*/
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

  
