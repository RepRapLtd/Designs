/*
 *  Incubator
 *
 *  Adrian Bowyer
 *  14 June 2004
 *
 */

#ifndef INCUBATOR_H
#define INCUBATOR_H

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
#include "strstream.h"// String i/o
#include "math.h"     // Sine cos etc

#define PORT "/dev/ttyS0"  // Port minicom talks to

// Turn n into hex in array h

void n2hex(int n, char* h);

// Turn hex in h into a number and return it

int hex2n(char* h);


#define ST_LEN 200           // Maximum command string length


#endif
