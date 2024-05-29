#define DATALENGTH 20


class Packet
{
public:
 Packet();
 boolean sendPacket(int sendTo,unsigned char D[], int l);
 boolean receivePacket(int &from,unsigned char D[], int &l);
 void printPacket(VirtuabotixPacket p)

private:

 void sendPacket()
 void sendPacket(char tgt, char m1, char m2, char m3)

 unsigned char addressTo;
 unsigned char addressFrom;
 unsigned char Length;
 unsigned char checkSum;
 unsigned char data[DATALENGTH];  
 boolean received;




 
};

