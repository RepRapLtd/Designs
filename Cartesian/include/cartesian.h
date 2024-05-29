/*
 *  Cartesian robot class
 *
 *  Adrian Bowyer
 *  8 October 2001
 *
 */

#ifndef CARTESIAN_H
#define CARTESIAN_H

#include "stdlib.h"   // System library
#include "stdio.h"    // Standard input/output definitions
#include "string.h"   // String function definitions
#include "unistd.h"   // UNIX standard function definitions
#include "sys/stat.h" // Env stuff...
#include "sys/types.h"// ...and the like
#include "fcntl.h"    // File control definitions
#include "errno.h"    // Error number definitions
#include "termios.h"  // POSIX terminal control definitions
#include "ctype.h"    // Useful character stuff
#include "iostream.h" // C++ console i/o
#include "fstream.h"  // C++ file i/o
#include <strstream>  // String i/o
#include "math.h"     // Sine cos etc

#define PORT "/dev/ttyS0"  // Port minicom talks to

// Turn n into hex in array h

void n2hex(int n, char* h);

// Turn hex in h into a number and return it

int hex2n(char* h);

// Convert 24-bit numbers to/from hex

long hex2long(char *h);
void long2hex(long n, char *h);

// Debugging on/off

void debug(int d);

// Class for the robot

#define scale (40.0)         // Steps/mm
#define speedsteps (1706.67) // Count = speedsteps/v
#define END_FIND 20000       // Steps to go to find zero/max
#define OFFSET 100           // Offset from hard zero
#define ST_LEN 200           // Maximum command string length
#define DEF_SC 768           // Default value of the speedcount
#define DEF_AC 368           // Default value of the accelleration count
#define DEF_IC 1             // Default value of the accelleration increment
#define DEF_SIC 1            // Default value of the steps per increment

class cartesian
{
 private:
  int fd;                 // RS232 port for the robot
  long xmax, ymax, zmax;  // Maximum axis positions
  int waiting;            // Robot active, so wait
  int setup;              // Flag for initializing - allows working outside envelope
  long mc;                // Move count
  long re_z;              // Re-zero every re_z moves
  double half_step;       // 1 for normal; 2 for half-stepping
  char* state_file;       // File name for storing the state
  int init;               // Has the structure been properly initialized?
  ofstream* dbo;          // Debug output stream

  // Send the string s to the robot

  void wr(char* str);

  // Read whatever the robot says (including nothing) into str

  void rd(char* str);

  // Read n bytes int str, waiting if need be
 
  void rd(int n, char* str);

  // Convert integer coordinates to mm

  void step2pos(long ia, long ib, long ic, double &x, double &y, double &z) const;

  // Convert mm to integer coordinates

  void pos2step(double x, double y, double z, long &ia, long &ib, long &ic) const;

  // Send destination

  int idest(long ia, long ib, long ic);

  int dest(double x, double y, double z);

  // Get position

  void ipos(long &ia, long &ib, long &ic);

  // Destination loaded - go there quick

  void q();

  // Destination loaded - go there at constant speed

  void g();

  // Save and load the robot's state

  int save();
  int load();
 public:
  // Set/get the speed and accelleration

  void set_speed(long speedcount, long acccount, long inccount, long stcount);
  void get_speed(long &speedcount, long &acccount, long &inccount, long &stcount);


  // Null Constructor

  cartesian();

  // Constructor with reset option

  cartesian(int rezero);

  // Destructor

  ~cartesian();

  // Copy constructor

  //cartesian(const cartesian& c);

  // Get the robot's current position

  void pos(double &x, double &y, double &z);

  // Get the robot's working envelope

  void envelope(double &x, double &y, double &z);
  
  // Move linearly to a position

  int go(double x, double y, double z);

  // Move to a position directly

  int quick(double x, double y, double z);

  // Move to the safe position (x =  0, y = 0, z = zmax)

  void safe();

  // Re-establish the zero position

  void re_zero();

  // Test and re-establish the zero position

  void zero_test();

  // Test and re-establish the zero position every n moves
  // Set n -ve to supress

  void repeat_zero(long n);

  // Set the speed, acceleration, etc

  int speed(double v, double rate, double dist);

  // Half stepping on (hs == 1) or off (hs = 0)

  void half(int hs);

  // Write a byte to the user port

  void user(int byte);

  // Read a byte from the user port

  unsigned char user();

  // Read a voltage from an A to D channel (answer is between 0.0 and 5.0)

  double volt(int c);

  // Set the user's endstop for X and Y (1 for on, 0 for off)

  void stop_xy(int on);

  // Set the user's endstop for Z (1 for on, 0 for off)

  void stop_z(int on);

  // Debug to file db_file (0 switches debugging off)

  void debug(char* db_file);

};

#endif
