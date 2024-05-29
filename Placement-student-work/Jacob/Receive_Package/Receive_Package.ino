#include <stdio.h>
#include "jacobs_packet.h"

#define MYADDRESS 12

VirtuabotixPacket myPacket; //this is where we declare an instance of the structure.

void sendPacket(VirtuabotixPacket p)
{
   p.checkSum = p.addressTo+p.data[0]+p.data[1]+p.data[2];
  Serial1.print("||");//send packet
  Serial1.write(p.addressTo);
  Serial1.write(p.data[0]);
  Serial1.write(p.data[1]);
  Serial1.write(p.data[2]);
  Serial1.write(p.checkSum);
  Serial.println("Packet sent 3");
}

void sendPacket(char tgt, char m1, char m2, char m3)
{
  myPacket.addressTo = tgt;
  myPacket.data[0]   = m1;
  myPacket.data[1]   = m2;
  myPacket.data[2]   = m3;
  sendPacket(myPacket);
  
}

void mydelay(long d)
{
   digitalWrite(18,LOW);
   delay(d-5);
   digitalWrite(18,HIGH);
   delay(5);
}








boolean listenforcommand()
{
  if(Serial1.available() >=7)
  {
    if(Serial1.read()=='|' && Serial1.read()=='|')
    {
      myPacket.received=true;
      myPacket.addressTo=Serial1.read();
      myPacket.data[0]=Serial1.read();
      myPacket.data[1]=Serial1.read();
      myPacket.data[2]=Serial1.read();
      myPacket.checkSum=Serial1.read();
      unsigned char tempCheck =myPacket.addressTo+myPacket.data[0]+myPacket.data[1]+myPacket.data[2];
      if (tempCheck != myPacket.checkSum)
      {
          myPacket.received=false;
          Serial.print("Error: ");
          Serial.print((char)myPacket.addressTo);
          Serial.print(' ');
          Serial.print((char)myPacket.data[0]);
          Serial.print(' ');
          Serial.print((char)myPacket.data[1]);
          Serial.print(' '); 
          Serial.print((char)myPacket.data[2]);
          Serial.print(' ');
          Serial.println(myPacket.checkSum);        
      }
    }
    else 
      myPacket.received=false; 
  } else 
     myPacket.received=false;
  return myPacket.received;
}


void setup()
{
   //Set up our serial port at the baud rate we wish to pass messages at
   Serial.begin(38400);
   Serial1.begin(1025000);
   //Additional setup items below
   //........we will set up an led to control
   pinMode(13, OUTPUT);
   digitalWrite(13, LOW);//let's turn off the LED on pin 13 for now.
   pinMode(18,OUTPUT);
   digitalWrite(18,LOW);
}

void loop()
{
   if(listenforcommand())//loop while messages are still in the queue
   {
      Serial.println ("Packet received");
      if (myPacket.received==true && myPacket.target=='T') //if our target "L"
      {
         if(myPacket.msg1 == 'A') 
            digitalWrite(13, HIGH); //turns on the LED
         else 
            digitalWrite(13, LOW); //turns off LED if the first message byte is not "H"
         //you could also use myPacket.msg2 for more command data
         //you could also use myPacket.msg3 for even more command data
      }
      if (myPacket.received==true && myPacket.target=='B') //optionally you can have up to 255 other targets
      {
         //you can add message processing here just like you did above
      }
   } //else
   sendPacket('T', 'A','B','C');
  mydelay(500);
}
     // Serial.println ("No Packet");



