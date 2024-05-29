#include <stdio.h>
#include "jacobs_packet.h"

#define MYADDRESS 12

VirtuabotixPacket myPacket; //this is where we declare an instance of the structure.

boolean debug = true;


void printPacket(VirtuabotixPacket p)
{
  Serial.print("Packet sent: ");
    Serial.print(p.Length);
    Serial.print(' ');
    Serial.print(p.addressTo);
    Serial.print(' ');
    Serial.print(p.checkSum);
    Serial.print(' ');    
    for(int i = 0; i<myPacket.Length; i++)
    {
      Serial.print((char)p.data[i]);
      Serial.print(' ');
    }
    Serial.println();
}




void sendPacket(VirtuabotixPacket p)
{
  p.addressFrom = MYADDRESS;
  p.checkSum = p.addressFrom + p.addressTo + p.data[0] + p.data[1] + p.data[2];
  Serial1.print("||");//send packet
  Serial1.write(p.Length);
  Serial1.write(p.addressFrom);
  Serial1.write(p.addressTo);
  Serial1.write(p.checkSum);
  Serial1.write(p.data[0]);
  Serial1.write(p.data[1]);
  Serial1.write(p.data[2]);
  
  if(debug)
    printPacket(p);
}
    
  

void sendPacket(char tgt, char m1, char m2, char m3)
{
  myPacket.addressTo = tgt;
  myPacket.data[0]   = m1;
  myPacket.data[1]   = m2;
  myPacket.data[2]   = m3;
  myPacket.Length = 3;
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
      myPacket.Length =Serial1.read();
      myPacket.addressFrom=Serial1.read();
      myPacket.addressTo=Serial1.read();
      myPacket.checkSum=Serial1.read();


      for(int i = 0; i<myPacket.Length; i++)
      {
        while(Serial1.available() <=0);
         myPacket.data[i]=Serial1.read();
      }
     


      unsigned char tempCheck =myPacket.addressFrom+myPacket.addressTo+myPacket.data[0]+myPacket.data[1]+myPacket.data[2];
      if (tempCheck != myPacket.checkSum)
      {
          myPacket.received=false;
          Serial.print("Checksum error: (");
          Serial.print(tempCheck);
          Serial.println(")");
          printPacket(myPacket);
          return  myPacket.received;     
      }
      if(myPacket.addressFrom == MYADDRESS)
      {
         Serial.println("Packet loop");
         myPacket.received=false; 
      }
      if(myPacket.addressTo != MYADDRESS)
      {
         sendPacket(myPacket);
         myPacket.received=false; 
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
   //Serial1.begin(300);
   //Additional setup items below
   //........we will set up an led to control
   pinMode(13, OUTPUT);
   digitalWrite(13, LOW);//let's turn off the LED on pin 13 for now.
   pinMode(18, OUTPUT);
}

void loop()
{


  
   if(listenforcommand())//loop while messages are still in the queue
   {
     if(debug)
     {
      Serial.println ("Packet received");
     }
      if (myPacket.received==true && myPacket.data[0]=='T') //if our target "L"
      {
         if(myPacket.data[1] == 'A') 
            digitalWrite(13, HIGH); //turns on the LED
         else 
            digitalWrite(13, LOW);
            
      }
      if (myPacket.received==true && myPacket.data[0]=='B') //optionally you can have up to 255 other targets
      {
         //you can add message processing here just like you did above
      }
   } //else
   sendPacket((char)11,'A','B','C');
   mydelay(10);
}
     // Serial.println ("No Packet");



