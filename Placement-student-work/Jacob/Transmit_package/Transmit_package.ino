#include <stdio.h>
#include "jacobs_packet.h"
//char tbs[6];//packet

#define MYADDRESS 17


VirtuabotixPacket myPacket;

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
/*          Serial.print((char)p.addressTo);
          Serial.print(' ');
          Serial.print((char)p.data[0]);
          Serial.print(' ');
          Serial.print((char)p.data[1]);
          Serial.print(' '); 
          Serial.print((char)p.data[2]);
          Serial.print(' ');
          Serial.println(p.checkSum);  
          */    
}




/*void sendPacket(char myTarget, int myMessage)
{
  if(myMessage > 999) myMessage= 999;//truncate data if it is too high.
  if(myMessage < 99) myMessage = 99;//truncate low data
  sprintf(tbs, "||%c%03d",myTarget,(int)myMessage );
  Serial1.print(tbs);//send packet
  Serial.println("Packet sent 2");
}*/


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
void setup()
{
  Serial.begin(38400);
  Serial1.begin(1025000);
    pinMode(13, OUTPUT);
   digitalWrite(13, LOW);

  pinMode(18,OUTPUT);
  digitalWrite(18,LOW);
}

void loop()
{
  //sendPacket with method 1: Send a preformatted packet to target
//  Serial1.print("||TABC");
  //Serial.println("Packet sent 1");
 // mydelay(500);
  //sendPacket with method 2: Sending a number between −99 and 999 to target
 // sendPacket('T', 900);
 // mydelay(500);
  //sendPacket with method 3: Sending 3 characters to target
  sendPacket('T', 'A','B','C');
  mydelay(500);
}


