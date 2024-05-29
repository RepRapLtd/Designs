/*
 *  Cartesian Robot driver
 *
 *  Adrian Bowyer
 *  19 September 2001
 *
 */

#include "cartesian.h"

// Turn n into hex in array h

void n2hex(int n, char* h)
{

  if (n < 0)
  {
    cerr << "n2hex: number -ve.\n";
    return;
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
  n = n & 0xffffff;
  int k0 = n%256;
  int k1 = ((n - k0)%65536);
  int k2 = (n - k0 - k1)/65536;
  k1 = k1/256;
  n2hex(k2, h);
  n2hex(k1,&(h[2]));
  n2hex(k0,&(h[4]));
}

// Debug to file db_file (0 switches debugging off)

void cartesian::debug(char* db_file)
{
  if(db_file)
  {
    dbo = new ofstream(db_file);
    if(!dbo)
      cerr << "Can't open debugging file " << db_file << endl;
    else
      *dbo << "Cartesian robot debug file: \n" << endl;
  } else
  {
    if(dbo)
    {
      *dbo << "\nDebugging shut down." << endl;
      dbo->close();
    }
    dbo = 0;
  }
}

// Send the string s to the robot

void cartesian::wr(char* str)
{

  // Check init (setup needs access before init is set)

   if(!init && !setup)
   {
     cerr << "Attempt to use robot before it's been initialized." << endl;
     if(dbo)
       *dbo << "  Attempt to use robot before it's been initialized." << endl;
   }

   if(waiting)
   {
     if(dbo)
       *dbo << "  wr(...) called while waiting." << endl;
     char s[3];
     rd(2, s);
     waiting = 0;
   }

   int n = write(fd, str, strlen(str));
   if(dbo)
   {
     *dbo << "  \"" << str << "\" sent to the robot.  ";
     *dbo << "write(...) call returned: " << n << endl;
   }
   if (n != strlen(str))
   {
     cerr << "write(...) failed on: \"" << str << "\"" << endl;
     if(dbo)
       *dbo << "  write(...) failed on: \"" << str << "\"" << endl;
   }
}

// Read whatever the robot says (including nothing) into s

void cartesian::rd(char* s)
{
    fcntl(fd, F_SETFL, FNDELAY);
    int nc = read(fd, s, 254);
    if(nc < 0)
	s[0] = 0;   // Nothing there
    else
	s[nc] = 0;
    if(dbo)
    {
      *dbo << "  \"" << s << "\" returned from the robot.  ";
      *dbo << "read(...) call returned: " << nc << endl;
    }
    fcntl(fd, F_SETFL, 0);
}

// Read n bytes, waiting if need be
 
void cartesian::rd(int n, char* s)
{
    int nc = read(fd, s, n);
    if(nc < 0)
	s[0] = 0;   // Nothing there
    else
	s[nc] = 0;
    if(nc != n)
    {
      cerr << "rd(" << n << "): read failed. Returned string: \"" << s << "\"" << endl;
      if(dbo)
      {
	*dbo << "  rd(" << n << "): read failed. Returned string: \"" << s << "\"" << endl;
        dbo->flush();
      }
    }

    if(dbo)
    {
      *dbo << "  \"" << s << "\" returned from the robot.  ";
      *dbo << "read(...) call returned: " << nc << endl;
    }
}

// Convert integer coordinates to mm

void cartesian::step2pos(long ia, long ib, long ic, double &x, double &y, double &z) const
{
  x = (double)ia/(scale*half_step);
  y = (double)ib/(scale*half_step);
  z = (double)ic/(scale*half_step);
}

// Convert mm to integer coordinates

void cartesian::pos2step(double x, double y, double z, long &ia, long &ib, long &ic) const
{
  ia = (long)(x*scale*half_step + 0.5);
  ib = (long)(y*scale*half_step + 0.5);
  ic = (long)(z*scale*half_step + 0.5);
}

// Send destination

int cartesian::idest(long ia, long ib, long ic)
{
  if(!setup)  // setup needs to go beyond the envelope
  {
    if( (ia > xmax) || (ib > ymax) || (ic > zmax) ||
	(ia < 0) || (ib < 0) || (ic < 0) ) 
      {
	if(dbo)
	  *dbo << "  Attempt to move outside the envelope to " << 
	    ia << ", " << ib << ", " << ic << endl;
	return(1);
      }
  }

  if(dbo)
    *dbo << " Sending coordinates: (" << ia << ", " << ib << ", " << ic << ") to the robot." << endl;

  char s[7];

  long2hex(ia, s);
  wr("A");
  wr(s);

  long2hex(ib, s);
  wr("B");
  wr(s);

  long2hex(ic, s);
  wr("C");
  wr(s);
  return(0);
}

int cartesian::dest(double x, double y, double z)
{
  long ia, ib, ic;
  pos2step(x, y, z, ia, ib, ic);
  return(idest(ia, ib, ic));
}

// Get position

void cartesian::ipos(long &ia, long &ib, long &ic)
{
  char s[7];
  wr("a");
  rd(6, s);
  ia = hex2long(s);
  wr("b");
  rd(6, s);
  ib = hex2long(s);
  wr("c");
  rd(6, s);
  ic = hex2long(s);

  if(dbo)
    *dbo << " Coordinates: (" << ia << ", " << ib << ", " << ic << ") received from the robot." << endl;

}

// Destination loaded - go there quickly

void cartesian::q()
{
  if(half_step > 1.5)
    wr("h");     // Half stepping
  else
    wr("q");     // Low torque

  wr("F");     // Fast move
  waiting = 1;
  mc++;
  if((re_z > 0) && (!(mc%re_z)))
    zero_test();
}

// Destination loaded - go there at constant speed

void cartesian::g()
{  
  if(half_step > 1.5)
    wr("h");     // Half stepping
  else
    wr("Q");     // High torque

  wr("f");     // Constant speed 
  waiting = 1;
  mc++;
  if((re_z > 0) && (!(mc%re_z)))
    zero_test();
}

// set speed and accelleration

void cartesian::set_speed(long speedcount, long acccount, long inccount, long stcount)
{
  char s[7];
  long2hex(speedcount, s);
  wr("T");
  wr(s);
  long2hex(acccount, s);
  wr("S");
  wr(s);
  long2hex(inccount, s);
  wr("J");
  wr(s);
  long2hex(stcount, s);
  wr("I");
  wr(s);
}

void cartesian::get_speed(long &speedcount, long &acccount, long &inccount, long &stcount)
{
  char s[7];

  wr("t");
  rd(6, s);
  speedcount = hex2long(s);

  wr("s");
  rd(6, s);
  acccount = hex2long(s);

  wr("j");
  rd(6, s);
  inccount = hex2long(s);

  wr("i");
  rd(6, s);
  stcount = hex2long(s);
}

// Null Constructor

cartesian::cartesian()
{
  state_file = 0;
  init = 0;
  dbo = 0;
  half_step = 1;
}

// Constructor

cartesian::cartesian(int rezero)
{
    waiting = 0;
    setup = 1;
    init = 0;
    dbo = 0;
    half_step = 1;
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
       cerr << "cartesian::cartesian(...): unable to open RS232 port" << endl;
    else
       fcntl(fd, F_SETFL, 0);

    state_file = 0;

    char* henv = getenv("HOME"); 
    mode_t mode = 0700; 
 
    if(!henv)  
      cerr << "Can't get $HOME environment variable\n";
    else
    {
	state_file = new char[strlen(henv) + strlen("/.cartesian/state") + 2]; 
 
	strcpy(state_file, henv); 
	strcat(state_file, "/.cartesian"); 
	if(access(state_file, W_OK)) 
	   if(mkdir(state_file, mode)) 
	   { 
	     cerr << "Can't create directory: " << state_file << endl;
	     delete [] state_file;
	     state_file = 0;
	   } else 
	     cout << "Creating directory: " << state_file << endl;
	strcat(state_file, "/state");
    }

    char s[100];

    wr(".");         // Reset robot
    usleep(100000);  // Wait...
    wr("e");         // Robot echo off
    usleep(100000);  // Wait...
    rd(s);           // Absorb whatever the robot has sent

    mc = 0;

    if(load())
    {

      // Didn't load from file, so re-initialize other data

      mc = -1;               // Force re-zero
    }

    if(rezero || (mc == -1))
    {
      mc = 0;
      re_zero();
    }

    mc = 0;
    re_z = -1;
    setup = 0;
    init = 1;
}

// Test and re-establish the zero position every n moves
// Set n -ve to supress

void cartesian::repeat_zero(long n)
{
  if(n <= 0)
    re_z = -1;
  else
    re_z = n;
}


// Test and re-set the zero position

void cartesian::zero_test()
{
  long x, y, z;

  ipos(x, y, z);

  safe();

  setup = 1;  

  idest(-END_FIND, 0, zmax);
  q();

  idest(0, -END_FIND, zmax);
  q();

  idest(0, 0, END_FIND);
  q();

  long xe, ye, ze;
  
  ipos(xe, ye, ze);

  if(dbo)
    *dbo << "Zero test. x error: " << OFFSET+xe << ", y error: " << OFFSET + ye <<
    ", z error: " << zmax + OFFSET - ze << endl;
  
  wr("r");

  idest(OFFSET, OFFSET, -OFFSET);
  g();
  idest(0, 0, zmax);
  wr("p");

  setup = 0;
  idest(x, y, zmax);
  q();
  idest(x, y, z);
  q();
}

// Re-establish the zero position

void cartesian::re_zero()
{
    setup = 1;
    wr("r");         // Set current position to 0
    idest(-END_FIND, 0, 0);
    q();

    wr("r");         // Set current position to 0
    idest(0, -END_FIND, 0);
    q();

    wr("r");         // Set current position to 0
    idest(0, 0, -END_FIND);
    q();

    wr("r");

    idest(OFFSET, OFFSET, OFFSET);
    g();
    wr("r");

    long d1, d2;
    idest(END_FIND, 0, 0);
    q();

    ipos(xmax, d1, d2);
    idest(xmax, END_FIND, 0);
    q();

    ipos(d1, ymax, d2);
    idest(xmax, ymax, END_FIND);
    q();

    ipos(d1, d2, zmax);

    xmax = xmax - OFFSET;
    ymax = ymax - OFFSET;
    zmax = zmax - OFFSET;

    idest(0, 0, zmax);
    q();
    setup = 0;
}


cartesian::~cartesian() 
{
  if(save())
  {
    cerr << "Can't save the robot's state in: " << state_file << endl;
    if(dbo)
      *dbo << "  Can't save the robot's state in: " << state_file << endl;
  }
  delete [] state_file;
  if(dbo)
  {
    *dbo << "~cartesian() called." << endl;
    dbo->close();
  }
  close(fd);
}

/*
cartesian::cartesian(const cartesian& c)
{
  fd = c.fd;
  xmax = c.xmax;
  ymax = c.ymax;
  zmax = c.zmax;
  waiting = c.waiting;
  strncpy(s, c.s, ST_LEN);
  setup = c.setup;
  mc = c.mc;
  init = c.init;
  state_file = new char[strlen(c.state_file)+3];
  strcpy(state_file, c.state_file);
}

*/

// Get the robot's current position

void cartesian::pos(double &x, double &y, double &z)
{
  long ia, ib, ic;
  ipos(ia, ib, ic);
  step2pos(ia, ib, ic, x, y, z);
}

// Get the robot's working envelope

void cartesian::envelope(double &x, double &y, double &z)
{
  step2pos(xmax, ymax, zmax, x, y, z);
}

// Move linearly to a position

int cartesian::go(double x, double y, double z)
{
  if(dest(x, y, z)) return(1);
  g();
  return(0);
}

// Move to a position directly

int cartesian::quick(double x, double y, double z)
{
  if(dest(x, y, z)) return(1);
  q();
  return(0);
}

// Move to the safe position (x =  0, y = 0, z = zmax)

void cartesian::safe()
{
  long ia, ib, ic;
  ipos(ia, ib, ic);
  idest(ia, ib, zmax);  // Straight up is safest
  q();
  idest(0, 0, zmax);
  q();
}


// Set the speed, acceleration, etc

int cartesian::speed(double v, double rate, double time)
{
  long speedcount, acccount, inccount, stcount;

  speedcount = (long)(0.5 + speedsteps/v);
  if(speedcount < 1) 
  {
    speedcount = 1;
    return(1);
  }

  // Acceleration distance

  double d = v*time + 0.5*rate*time*time;
  acccount = (long)(0.5 + d*scale*half_step);

  // Acceleration gradient

  double final_v = v + rate*time;
  long delta_count = (long)(0.5 + speedsteps/final_v) - speedcount;
  if(delta_count < acccount)
  {
    inccount = 1;
    stcount = (long)(0.5 + (double)acccount/(double)delta_count);
  } else
  {
    inccount = (long)(0.5 + (double)delta_count/(double)acccount);
    stcount = 1;
  }

  set_speed(speedcount, acccount, inccount, stcount);

  return(0);
}

// Half stepping on (hs == 1) or off (hs = 0)

void cartesian::half(int hs)
{
  if(hs)
  {
    half_step = 2;

  } else
  {
    half_step = 1;

  }
}


// Save and load the robot's state

int cartesian::save()
{
  if(!state_file) return(1);
  ofstream op(state_file);
  if(!op) return(1);

  op << half_step << '\n';
  long ia, ib, ic;
  ipos(ia, ib, ic);
  op << ia << ' ' << ib << ' ' << ic << '\n';
  op << xmax << ' ' << ymax << ' ' << zmax << '\n';
  op << mc << '\n';
  long speedcount, acccount, inccount, stcount;
  get_speed(speedcount, acccount, inccount, stcount);
  op << speedcount << '\n';
  op << acccount << '\n';
  op << inccount << '\n';
  op << stcount << '\n';
  op << init << '\n';
  op.close();
  return(0);
}

int cartesian::load()
{
  if(!state_file) return(1);
  ifstream ip(state_file);
  if(!ip) return(1);

  ip >> half_step;
  long ia, ib, ic;
  ip >> ia >> ib >> ic;
  idest(ia, ib, ic);
  wr("p");
  ip >> xmax >> ymax >> zmax;
  ip >> mc;
  long speedcount, acccount, inccount, stcount;
  ip >> speedcount;
  ip >> acccount;
  ip >> inccount;
  ip >> stcount;
  set_speed(speedcount, acccount, inccount, stcount);
  ip >> init;
  ip.close();
  return(0);
}


// Write a byte to the user port

void cartesian::user(int byte)
{
  char s[4];

  wr("L00");
  wr("K");
  n2hex(byte, s);
  wr(s);
}

// Read a byte from the user port

unsigned char cartesian::user()
{
  char s[4];

  wr("L3f");
  wr("k");
  rd(2, s);
  unsigned char r = hex2n(s);
  return r;
}

// Read a voltage from an A to D channel (answer is between 0.0 and 5.0)

double cartesian::volt(int c)
{
  return 0;
}

// Set the user's endstop for X and Y (1 for on, 0 for off)

void cartesian::stop_xy(int on)
{

}

// Set the user's endstop for Z (1 for on, 0 for off)

void cartesian::stop_z(int on)
{

}
