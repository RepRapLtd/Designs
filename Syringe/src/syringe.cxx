/*
 *  Syringe driver
 *
 *  Adrian Bowyer
 *  2 May 2005
 *
 */

#include "syringe.h"

long fd;
char s[255];

// Send the string s to the robot

void wr(char* str)
{
     long n = write(fd, str, strlen(str));
     if (n < 0)
       cerr << "wr failed on: \"" << str << "\"" << endl;
}

// Read whatever the robot says (including nothing) into s

void rd()
{
      fcntl(fd, F_SETFL, FNDELAY);
      long nc = read(fd, s, 254);
      if(nc < 0)
	s[0] = 0;   // Nothing there
      else
	s[nc] = 0;
      fcntl(fd, F_SETFL, 0);
}

// Read n bytes, waiting if need be
 
void rd(long n)
{
      long nc = read(fd, s, n);
      if(nc != n)
	cerr << "rd(n): read failed.\n";
      else
	s[nc] = 0;
}

// Initialize everything

void init()
{
      fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
      if (fd == -1)
         cerr << "init: Unable to open" << endl;
      else
         fcntl(fd, F_SETFL, 0);


      wr("e");         // Syringe echo off
      usleep(100000);  // Wait...
      rd();            // Absorb whatever the syringe has sent
}

// Turn n into hex in array h

void n2hex(long n, char* h)
{
  if (n < 0)
  {
    cerr << "n2hex: number -ve.\n";
    n = 0;
  }

  if (n > 255)
  {
    cerr << "n2hex: number > 255.\n";
    n = 255;
  }

  long d = n & 0xf;
  if(d > 9)
    d = d - 10 + 'a';
  else
    d = d + '0';

  h[1] = d;

  d = n >> 4;
  if(d > 9)
    d = d - 10 + 'a';
  else
    d = d + '0';

  h[0] = d;
  h[2] = 0;
}

// Turn hex in h into a number and return it

long hex2n(char* h)
{
  long d = h[1];
  if(isalpha(d))
    d = d - 'a' + 10;
  else
    d = d - '0';
  long e = h[0];
  if(isalpha(e))
    e = e - 'a' + 10;
  else
    e = e - '0';
  return(16*e + d);
}

// Convert 24-bit numbers to/from hex

long hex2long(char *h)
{

  long n = 65536*hex2n(h) + 256*hex2n(&(h[2])) + hex2n(&(h[4]));
  if(h[0] == 'f')
    n = n | (((long)-1) ^ 0xffffff);
  return(n);
}

void long2hex(long n, char *h)
{
  int k0 = n%256;
  int k1 = ((n - k0)%65536);
  int k2 = (n - k0 - k1)/65536;
  k1 = k1/256;
  n2hex(k2, h);
  n2hex(k1,&(h[2]));
  n2hex(k0,&(h[4]));
}

// Get the syringe's current position and delay setting

void pos(long &a, long &b, long& c)
{
  wr("a");
  rd(6);
  a = hex2n(s);
  wr("b");
  rd(6);
  b = hex2n(s);
  wr("d");
  rd(6);
  c = hex2n(s);
}

// Move axis to position a directly

void move(long a)
{
  long2hex(a, s);
  wr("B");
  wr(s);
  s[0] = 'x';
  s[1] = 0;
  wr(s);
}


// New step delay value

void set_delay(long a)
{
  long2hex(a, s);
  wr("D");
  wr(s);
}



// Send and receive data directly to/from the robot

void talk()
{
  long loop = 1;

  while(loop)
  {
    cout << "String to send (r to return): ";
    cin >> s;
    if(s[0] != 'r')
    {
      wr(s);
      sleep(1);
      rd();
      if(s[0]) cout << "Response: " << s << endl;
    } else
      loop = 0;
  }
}



int main()
{
  long a, b, c, d;
  long n;
  char k;

  init();  // Get show on road...

  // Loop, reading commands and acting on them

  do
  {
    cout << "Command: ";
    cin >> k;
    switch(k)
    {
    case 't':
      talk();
      break;

    case 'p':
      pos(a, b, c);
      cout << "syringe: " << a << " axis: " << b << " delay: " << c << endl;
      break;

    case 'm':
      cout << "axis position: ";
      cin >> a;
      move(a);
      break;

   case 'd':
      cout << "delay value: ";
      cin >> a;
      set_delay(a);
      break;

    case 'n':
      pos(a, b, c);
      cout << "axis position to move to repeatedly: ";
      cin >> d;
      cout << "number of times to do that: ";
      cin >> n;
      for(long i = 0; i < n; i++)
      {
         move(d);
         usleep(100000);  // Wait...
	 move(a);
         usleep(100000);  // Wait...
      }
      break;

    case 'q':
      break;

    default:
      cout << "Commands are:\n";
      cout << "t - talk\n";
      cout << "d - set step delay\n";
      cout << "p - print state\n";
      cout << "m - move axis to position\n";
      cout << "n - do many repeated movements\n";
      cout << "q - quit\n";
      cout << endl;
    }
  } while(k != 'q');

  close(fd);
  return(0);
}
