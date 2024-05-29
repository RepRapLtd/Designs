/*
 *  Robot leg driver
 *
 *  Adrian Bowyer
 * 13 September 2000
 *
 */

#include "rob.h"

int fd;
char s[255];

// Send the string s to the robot

void wr(char* str)
{
     int n = write(fd, str, strlen(str));
     if (n < 0)
       cerr << "wr failed on: \"" << str << "\"" << endl;
}

// Read whatever the robot says (including nothing) into s

void rd()
{
      fcntl(fd, F_SETFL, FNDELAY);
      int nc = read(fd, s, 254);
      if(nc < 0)
	s[0] = 0;   // Nothing there
      else
	s[nc] = 0;
      fcntl(fd, F_SETFL, 0);
}

// Read n bytes, waiting if need be
 
void rd(int n)
{
      int nc = read(fd, s, n);
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


      wr("e");         // Robot echo off
      usleep(100000);  // Wait...
      rd();            // Absorb whatever the robot has sent
}

// Turn n into hex in array h

void n2hex(int n, char* h)
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

  int d = n & 0xf;
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

int hex2n(char* h)
{
  int d = h[1];
  if(isalpha(d))
    d = d - 'a' + 10;
  else
    d = d - '0';
  int e = h[0];
  if(isalpha(e))
    e = e - 'a' + 10;
  else
    e = e - '0';
  return(16*e + d);
}

// Get the robot's current position

void pos(int &a, int &b, int& c)
{
  wr("A");
  rd(2);
  a = hex2n(s);
  wr("B");
  rd(2);
  b = hex2n(s);
  wr("C");
  rd(2);
  c = hex2n(s);
}

// Move to a position directly

void quick(int a, int b, int c)
{
  char t[3];

  n2hex(a, t);
  wr("0");
  wr(t);

  n2hex(b, t);
  wr("1");
  wr(t);

  n2hex(c, t);
  wr("2");
  wr(t);
}

// Use a dda to move slowly and linearly to a position

void slow(int a1, int b1, int c1)
{
  int a0, b0, c0, a, b, c;

  pos(a0, b0, c0);  // Where are we?

  dda d = dda(a0, b0, c0, a1, b1, c1);

  do
  {
    d.point(a, b, c);
    quick(a, b, c);
    usleep(STEP);     // Delay to let the robot get there
  } while(d.step());
}

// Send and receive data directly to/from the robot

void talk()
{
  int loop = 1;

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

// Generate a random position

void ran(int& a, int& b, int& c)
{
  long r;
  do
  {
     a = lrand48() & 0xff;
  } while( a < 15 || a > 240);
  do
  {
     b = lrand48() & 0xff;
  } while( b < 128 || b > 240);
  do
  {
     c = lrand48() & 0xff;
  } while( c < 15 || c > 240);
}



int main()
{
  int a, b, c;
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
      cout << "a: " << a << " b: " << b << " c: " << c << endl;
      break;

    case 'm':
      cout << "A, B, and C positions: ";
      cin >> a;
      cin >> b;
      cin >> c;
      quick(a, b, c);
      break;

    case 'g':
      cout << "A, B, and C positions: ";
      cin >> a;
      cin >> b;
      cin >> c;
      slow(a, b, c);
      break;

    case 'r':

      cout << "Number of random movements: ";
      cin >> n;
      for(long i = 0; i < n; i++)
      {
	 ran(a, b, c);
         cout << i << "/" << n << " a: " << a << " b: " << b << " c: " << c << endl;
         slow(a, b, c);
      }
      break;

    case 'q':
      break;

    default:
      cout << "Commands are:\n";
      cout << "t - talk\n";
      cout << "p - print position\n";
      cout << "m - move quickly to position\n";
      cout << "g - go linearly to position\n";
      cout << "r - random movements\n";
      cout << "q - quit\n";
      cout << endl;
    }
  } while(k != 'q');

  close(fd);
  return(0);
}
