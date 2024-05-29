/*
 *  Syringe driver
 *
 *  Adrian Bowyer
 *  3 May 2005
 *
 */

#ifndef SYRINGE_H
#define SYRINGE_H

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

// Swap a pair of integers

inline void swp(int& a, int& b)
{
  int t;
  t = a;
  a = b;
  b = t;
}

// 3-dimensional Bressenham DDA

class dda
{
 private:

  // x, y, z are the current point
  // xo, yo, zo are the start point
  // xd, yd, zd are the differences between the start and end
  // iy, iz are the y and z DDA sums
  // nx, ny, nz are flags for the x, y, and z differences being negative
  // sxy and sxz are flags to swap x and y, and to swap x and z

  int x, y, z, xo, yo, zo, xd, yd, zd, iy, iz, nx, ny, nz, sxy, sxz;

 public:

  // Constructor initializes everything given where we are and where
  // we want to go.

  dda(int x0, int y0, int z0, int x1, int y1, int z1)
  {
    xo = x0;
    yo = y0;
    zo = z0;
    xd = x1 - x0;
    yd = y1 - y0;
    zd = z1 - z0;
    if(nx = (xd < 0)) xd = -xd;
    if(ny = (yd < 0)) yd = -yd;
    if(nz = (zd < 0)) zd = -zd;
    if(sxy = (xd < yd)) swp(xd, yd);
    if(sxz = (xd < zd)) swp(xd, zd);
    x = 0;
    y = 0;
    z = 0;
    iy = -xd/2;
    iz = iy;
  }

  // Return the current point, given all the negates and swaps

  void point(int& a, int& b, int& c)
  {
    a = x;
    b = y;
    c = z;
    if(sxz) swp(a, c);
    if(sxy) swp(a, b);
    if(nx) a = -a;
    if(ny) b = -b;
    if(nz) c = -c;
    a = a + xo;
    b = b + yo;
    c = c + zo;
  }

  // Take 1 step of the DDA.
  // Return 1 if we're still going, 0 if we've finished

  int step()
  {
    x++;

    iy = iy + yd;
    if(iy > 0)
    {
      iy = iy - xd;
      y++;
    }

    iz = iz + zd;
    if(iz > 0)
    {
      iz = iz - xd;
      z++;
    }
    return(x <= xd);
  }
};

#endif
