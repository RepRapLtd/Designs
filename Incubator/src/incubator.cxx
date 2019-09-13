
/*
 *  Incubator
 *
 *  Adrian Bowyer
 *  14 June 2004
 *
 */

#include "incubator.h"

int dbo = 0;
int fd;

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


// Send the string str to the incubator

void wr(char* str)
{

   int n = write(fd, str, strlen(str));
   if(dbo)
   {
     cerr << "  \"" << str << "\" sent to the incubator.  ";
     cerr << "write(...) call returned: " << n << endl;
   }
   if (n != strlen(str))
   {
     cerr << "write(...) failed on: \"" << str << "\"" << endl;
   }
}

// Read whatever the incubator says (including nothing) into s

void rd(char* s)
{
    fcntl(fd, F_SETFL, FNDELAY);
    int nc = read(fd, s, 254);
    if(nc < 0)
        s[0] = 0;   // Nothing there
    else
        s[nc] = 0;
    if(dbo)
    {
      cerr << "  \"" << s << "\" returned from the incubator.  ";
      cerr << "read(...) call returned: " << nc << endl;
    }
    fcntl(fd, F_SETFL, 0);
}

// Read n bytes, waiting if need be

void rd(int n, char* s)
{
    int nc = read(fd, s, n);
    if(nc < 0)
        s[0] = 0;   // Nothing there
    else
        s[nc] = 0;
    if(nc != n)
    {
      cerr << "rd(" << n << "): read failed. Returned string: \"" << s << "\"" << endl;
    }

    if(dbo)
    {
      cerr << "  \"" << s << "\" returned from the robot.  ";
    }
}


void init()
{
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
       cerr << "cartesian::cartesian(...): unable to open RS232 port" << endl;
    else
       fcntl(fd, F_SETFL, 0);

    char s[100];

    wr("r");         // Reset robot
    usleep(100000);  // Wait...
    wr("e");         // Robot echo off
    usleep(100000);  // Wait...
    rd(s);           // Absorb whatever the robot has sent
}

// Get the temperature

int iget_temp()
{
  char h[5];
  wr("p");
  rd(2, h);
  return hex2n(h);
}

double get_temp() { return (double)iget_temp(); }

void peltier_on()
{
  wr("1");
}

void peltier_off()
{
  wr("0");
}

void cool()
{
  wr("c");
  sleep(1);
  peltier_on();
  sleep(1);
}

void heat()
{
  wr("h");
  sleep(1);
  peltier_on();
  sleep(1);
}

// Man program is just a logging loop

int main(int argc, char** argv)
{

  if(argc != 2)
  {
    cerr << "Usage: cart_test log_file" << endl;
    return 1;
  }

  ofstream log(argv[1]);

  //double t, temp = 0;
  int val, target, diff;

  init();

  cout << "Target temperature: ";
  cin >> target;

  do
  {
    //cout << "Temperature: ";
    //cin >> temp;
    val = iget_temp();
    diff = target - val;
    if(abs(diff) > 1)
    {
      if(diff < 0) // Hotter -> smaller number
      {
	heat();
	cout << "Heating." << endl;
      }else
      {
	cool();
	cout << "Cooling." << endl;
      }
    } else
    {
      peltier_off();
      cout << "Peltier off." << endl;
    }
    cout << target << "\t" << val << '\n'; 
    log << target << "\t" << val << '\n';
    sleep(10);
  }while(1);

  return(0);
}
