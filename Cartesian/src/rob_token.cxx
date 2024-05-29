/*
 *  Robot leg driver
 *
 *  Adrian Bowyer
 * 13 September 2000
 *
 */

#include "rob.h"


int fd;                // File descriptor for output port
int current_log = 0;   // Log servo current consumptions during movement
long delay = 0;        // Time delay between steps
int debug = 1;         // Debugging

// Turn n into hex in array h

void n2hex(uc n, char* h)
{
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

// Write out a packet in hex

void hexout(uc* packet)
{
  char h[3];
  for(int i = 0; i < PL; i++)
  {
    n2hex(packet[i], h);
    cout << h[0] << h[1] << ' ';
  }
  cout.flush();
}

// Send a packet to the robot

void write_packet(uc* packet)
{     
     int n = write(fd, packet, PL);

     if (n < 0)
     {
       cout << "write_packet failed on: ";
       hexout(packet);
       cout << endl;
     } else if(debug)
     {
       cout << '\n';
       hexout(packet);
       cout << " sent" << endl;
     }
}

int read_packet(uc* packet)
{
      int nc = read(fd, packet, PL);
      if(nc != PL)
	cerr << "read_packet failed.  Returned: " << nc << endl;
      else if(debug)
      {
         cout << '\n';
         hexout(packet);
         cout << " received" << endl;
      }
      // Pass it on?

      if(packet[0] != ME)
	write_packet(packet);

      // Is it for me?

      return(packet[0] == ME);
}  

// Initialize everything

void init()
{
      fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
      if (fd == -1)
         cerr << "init: Unable to open" << endl;
      else
         fcntl(fd, F_SETFL, 0);

      usleep(100000);  // Wait...
}

// Get three values from a PIC

void three_in(uc &a, uc &b, uc &c, uc pic, char command)
{
  uc p[PL];
  p[0] = pic;
  p[1] = ME;
  p[2] = command;
  write_packet(p);
  usleep(delay);
  while(!read_packet(p));
  if(p[2] != command - 'A' + 'a')
  {
    cout << ": unexpected packet returned: ";
    hexout(p);
    cout << endl;
  }
  a = p[3];
  b = p[4];
  c = p[5];
}

// Send three values to a PIC

void three_out(uc a, uc b, uc c, uc pic, char command)
{
  uc p[PL];
  p[0] = pic;
  p[1] = ME;
  p[2] = command;
  p[3] = a;
  p[4] = b;
  p[5] = c;
  write_packet(p);
}

// Get the current position

void pos(uc &a, uc &b, uc &c, uc pic)
{
  three_in(a, b, c, pic, 'V');
}

// Get the current current (!) consumption

void current(uc &a, uc &b, uc &c, uc pic)
{
  three_in(a, b, c, pic, 'I');
}

// Move to a position directly

void quick(uc a, uc b, uc c, uc pic)
{
  three_out(a, b, c, pic, 'T');
}

// Use a dda to move slowly and linearly to a position

void slow(int a1, int b1, int c1, uc pic)
{
  int a0, b0, c0, a, b, c;
  uc aa, bb, cc;

  pos(aa, bb, cc, pic);  // Where are we?
  a0 = aa;
  b0 = bb;
  c0 = cc;

  dda d = dda(a0, b0, c0, a1, b1, c1);

  do
  {
    d.point(a, b, c);
    quick(a, b, c, pic);
    usleep(delay);     // Delay to let the robot get there
    if(current_log)
    {
      current(aa, bb, cc, pic);
      cout << "Current: " << (int)aa << ' ' << (int)bb << ' ' << (int)cc << CR;
      cout.flush();
    }
    usleep(STEP-delay);
  } while(d.step());
  if(current_log) cout << endl;
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


// Reset a pic

void reset(uc pic)
{
  three_out(0, 0, 0, pic, 'R');
}


int main()
{
  int a, b, c;
  uc aa, bb, cc;
  long n;
  char k;
  int pic = 1;

  init();  // Get show on road...

  // Loop, reading commands and acting on them

  do
  {
    cout << "Command for pic " << pic << ": ";
    cin >> k;
    switch(k)
    {

    case 'i':
      current_log = !current_log;
      cout << "Current logging ";
      if(current_log)
	cout << "on." << endl;
      else
	cout << "off." << endl;
      break;

    case 'd':
      cout << "Delay (0 - " << STEP << "): ";
      cin >> delay;
      break;

    case 'p':
      pos(aa, bb, cc, pic);
      cout << "a: " << (int)aa << " b: " << (int)bb << " c: " << (int)cc << endl;
      break;

    case 'm':
      cout << "A, B, and C positions: ";
      cin >> a;
      cin >> b;
      cin >> c;
      quick(a, b, c, pic);
      break;

    case 'g':
      cout << "A, B, and C positions: ";
      cin >> a;
      cin >> b;
      cin >> c;
      slow(a, b, c, pic);
      break;

    case 'r':

      cout << "Number of random movements: ";
      cin >> n;
      for(long i = 0; i < n; i++)
      {
	 ran(a, b, c);
         cout << i << "/" << n << " a: " << a << " b: " << b << " c: " << c << endl;
         slow(a, b, c, pic);
      }
      break;

    case 'R':
      reset(pic);

    case 'P':
      cout << "Current pic is " << pic << ".  New one: ";
      cin >> pic;
      break;

    case 'D':
      debug = !debug;
      cout << "Debugging is ";
      if(debug)
	cout << "ON";
      else
	cout << "OFF";
      cout << '.' << endl;
      break;

    case 'q':
      break;

    default:
      cout << "Commands are:\n";
      cout << "p - print position\n";
      cout << "m - move quickly to position\n";
      cout << "d - set current logging delalay\n";
      cout << "i - current logging on/off\n";
      cout << "R - reset\n";
      cout << "g - go linearly to position\n";
      cout << "r - random movements\n";
      cout << "P - change pic being talked to\n";
      cout << "D - debug on/off\n";
      cout << "q - quit\n";
      cout << endl;
    }
  } while(k != 'q');

  close(fd);
  return(0);
}
