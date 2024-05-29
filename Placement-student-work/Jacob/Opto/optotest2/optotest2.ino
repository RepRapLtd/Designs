/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc

 The circuit:
 * Any serial device attached to Serial port 1
 * Serial monitor open on Serial port 0:

 created 30 Dec. 2008
 modified 20 May 2012
 by Tom Igoe & Jed Roach
 modified 27 Nov 2015
 by Arturo Guadalupi

 This example code is in the public domain.

 */
String stringOne, stringTwo;
int i = 0;

void setup() 
{
  Serial.begin(121212);
  Serial1.begin(4000000);
    stringOne = String("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
 
 

}

void loop() 
{
  Serial.println("\n\nComparing Strings:");
  Serial.println();
 Serial1.println(stringOne);
 stringTwo = Serial1.readString();
  Serial.println(stringTwo);
i++;
  if (stringOne.equals(stringTwo)) {
    Serial.println(stringOne + " equals " + stringTwo);
  }else {
    Serial.println(stringOne + " does not equal " + stringTwo);
  }
  Serial.println(stringOne.length());
  stringTwo.remove(26);
Serial.println(stringTwo.length());

if(i > 26)
  {
    Serial.write('\n');
    i = 0;
    delay(1);
    digitalWrite(18, 0);
    delay(10);
    digitalWrite(18,1);
    delay(1);
  }
}
