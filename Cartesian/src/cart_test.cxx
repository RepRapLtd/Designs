#include "cartesian.h"

// Read in a file of coordinates and execute it

int do_file(char* f_name, cartesian* c)
{
  ifstream ip(f_name);
  if(!ip)
  {
    cerr << "Can't open file: " << f_name << endl;
    return 1;
  }

  double x, y, z;
  int q;

  long count = 1;

  cout << endl;

  while(!ip.eof())
  {
    ip >> q >> x >> y >> z;
    if(q)
    {
      cout << "Move " << count << " quick to " << x << ", " << 
	y << ", " << z << endl;
      c->quick(x, y, z);
    } else
    {
      cout << "Move " << count << " slow to " << x << ", " << 
	y << ", " << z << endl;
      c->go(x, y, z);
    }
    count++;
  }
  cout << endl;
  ip.close();
  return 0;
}

// Man program is just a big command loop

int main(int argc, char** argv)
{
  char k;
  cartesian* c = 0;

  if(argc > 3)
  {
    cerr << "Usage: cart_test [-r] [move_file]" << endl;
    return 1;
  }

  int ac = 1;
  while(ac < argc)
  {
    if(!strcmp("-r", argv[ac]))
       c = new cartesian(1);
    else
    {
      if(!c) c = new cartesian(0);
      if(!do_file(argv[ac], c))
      {
	c->safe();
	delete c;
	return 0;
      }
    }
    ac++;
  }

  if(!c) c = new cartesian(0);

  double x, y, z, x1, y1, z1, r, theta;
  long speedcount, acccount, inccount, stcount;
  int byte;
  long stp, lp, rz;
  char f_name[200];

  c->envelope(x, y, z);

  cout << "envelope: " << x << "  " << y << "  " << z << endl;

  // Loop, reading commands and acting on them

  c->user(4);

  do
  {
    cout << "Command: ";
    cin >> k;
    switch(k)
    {
    case 'p':
      c->pos(x, y, z);
      cout << "Position: " << x << ", " << y << ", " << z << " mm" << endl;
      break;

    case 'a':
      cout << "X, Y, Z to accelerate and decelerate to (mm): ";
      cin >> x >> y >> z;
      if(c->quick(x, y, z))
      {
	cerr << "Illegal position.\n";
	c->envelope(x, y, z);
        cerr << "Robot's envelope is: " << x << "  " << y << "  " << z << endl;
      }
      break;

    case 'b':
      byte = c->user();
      cout << "User port byte: " << byte << endl;
      break;

    case 'B':
      cout << "Byte to send: ";
      cin >> byte;
      c->user(byte);
      break;

    case 'g':
      cout << "X, Y, Z to move at constant speed to (mm): ";
      cin >> x >> y >> z;
      if(c->go(x, y, z))
      {
	cerr << "Illegal position.\n";
	c->envelope(x, y, z);
        cerr << "Robot's envelope is: " << x << "  " << y << "  " << z << endl;
      }
      break;

    case 'G':
      cout << "X, Y, Z to move at constant speed to (mm): ";
      cin >> x >> y >> z;
      c->user(0);
      if(c->go(x, y, z))
      {
	cerr << "Illegal position.\n";
	c->envelope(x, y, z);
        cerr << "Robot's envelope is: " << x << "  " << y << "  " << z << endl;
      }
      c->user(4);
      break;

    case 's':
      c->safe();
      break;

    case '0':
      c->re_zero();
      break;

    case 'v':
      cout << "Velocity (mm/s): ";
      cin >> x;
      cout << "Rate (mm/s^2): ";
      cin >> y;
      cout << "Time (s): ";
      cin >> z;
      c->speed(x, y, z);
      break;

    case 'c':
      cout << "Centre (x, y): ";
      cin >> x >> y;
      cout << "Height (z): ";
      cin >> z;
      cout << "Radius: ";
      cin >> r;
      cout << "Steps: ";
      cin >> stp;
      c->pos(x1, y1, z1);
      c->quick(x+r, y, z1);
      c->go(x+r, y, z);
      for(long i = 0; i <= stp; i++)
      {
	theta = 2*M_PI*(double)i/(double)stp;
	x1 = x + r*cos(theta);
	y1 = y + r*sin(theta);
	c->go(x1, y1, z);
      }
      c->quick(x1, y1, z1);
      break;

    case 'D':
      cout << "File name for debugging information: ";
      cin >> f_name;
      c->debug(f_name);
      cout << "Debugging is ON." << endl;
      break;

    case 'd':
      c->debug(0);
      cout << "Debugging is OFF." << endl;
      break;

    case 'f':
    case 'F':
      cout << "Name of the coordinate file: ";
      cin >> f_name;
      if(k == 'F')
      {
	cout << "Number of times to loop file: ";
	cin >> lp;
	for(long i = 0; i < lp; i++)
	  do_file(f_name, c);
      } else
	do_file(f_name, c);
      break;

    case 't':
      c->zero_test();
      break;

    case 'H':
      c->half(1);
      cout << "Half stepping is ON." << endl;
      break;

    case 'h':
      c->half(0);
      cout << "Half stepping is OFF." << endl;
      break;

    case 'z':
      cout << "Re-zero after how many moves (-ve to supress)? ";
      cin >> rz;
      c->repeat_zero(rz);
      break;

    case 'n':
      c->get_speed(speedcount, acccount, inccount, stcount);
      cout << "Steps per delay: " << speedcount << endl;
      cout << "Steps to accelerate/decelerate for: " << acccount << endl;
      cout << "Change speed every " << inccount << " steps\n";
      cout << "Change speed by " << stcount << " steps" << endl;
      break;

    case 'N':
      cout << "Steps per delay: "; 
      cin >> speedcount;
      cout << "Steps to accelerate/decelerate for: ";
      cin >> acccount;
      cout << "When accelerating, change speed after how many steps: ";
      cin >> inccount;
      cout << "When accelerating, change speed by how many steps: ";
      cin >> stcount;
      c->set_speed(speedcount, acccount, inccount, stcount);
      break;

    case 'q':
      break;

    default:
      cout << "Commands are:\n";
      cout << "D - debug on\n";
      cout << "d - debug off\n";      
      cout << "p - print position\n";
      cout << "a - accelerate and decelerate to a position\n";
      cout << "g - move at constant speed to a position\n";
      cout << "G - move at constant speed to a position with user on/off\n";
      cout << "H - half-stepping ON\n";
      cout << "h - half-stepping OFF\n";
      cout << "n - print the accelleration parameters\n";
      cout << "N - set the acceleration parameters\n";
      cout << "s - move to the safe position\n";
      cout << "b - reat a byte from the user port\n";
      cout << "B - write a byte to the user port\n";
      cout << "0 - re-establish the origin\n";
      cout << "v - set speed and acceleration\n";
      cout << "c - describe a circle\n";
      cout << "f - read moves from a file and execute them\n";
      cout << "F - read moves from a file and execute them in a loop\n";
      cout << "t - test and re-establish the zero position\n";
      cout << "z - test and re-establish the zero position every n moves\n";
      cout << "q - quit\n";
      cout << endl;
    }
  } while(k != 'q');

  delete c;

  return(0);
}
