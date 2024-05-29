#define DATALENGTH 20


struct VirtuabotixPacket 
{
 unsigned char addressTo;
 unsigned char addressFrom;
 unsigned char Length;
 unsigned char checkSum;
 unsigned char data[DATALENGTH];  
  
 boolean received;
};
