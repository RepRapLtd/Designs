/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
#include "Globals.h"

/* FINGER MOTORS*/
struct fingerType finger[NUM_OF_FINGERS];
/* DEMO MODE */
int inactivityCounter=0;		// amount of time the hand has been inactive for, used for demo mode
int demoModeInnactivityTime;	// number of seconds of inactivity for demo mode screen saver
int demoModeCounter=0;			// counts through grips of demo mode
int demoGripDuration = 1700;	// amount of time each grip runs in demo mode (in milliseconds)
int demoOnce = 0;
/* SERIAL CONTROL */
char buffer[MAX_BUF];	// buffer and variable to store incoming Serial string
int strLength=0;		// how much is in the buffer
// holds the command received over Serial
int valueList[4];       // string tokens (finger,direction,stop thresh,speed)
int advancedCmd=-1;
int instructionsCmd=-1;
int muscleCmd=-1;
int gripCmd=-1;
int handCmd=-1;
int demoCmd=-1;
/* TEXT STRINGS */
char* dirNameString[] = {"Open","Close","OFF","ON","Right","Left"};				// directions
char* gripNameString[] = {"Fist","Palm","Thumbs Up","Point","Pinch","Tripod"};	// grip names
/* FINGERS */
int currentDir=0;
int fingerPositions[2] = {FULLY_OPEN, FULLY_CLOSED};
int fingerCounter = 0;
/* Muscle sensing */
int musclePinList[2];					// muscle sense ADC pin names
int muscleReadings[2][NUM_SAMPLES];		// all muscle readings
int prevSignalDir[2];					// previous signal direction
int prevPeaks[2][NUM_PEAKS];			// all peak readings
int peakAverage[2];						// average of peaks to calculate threshold value
int noiseFloor[2];						// average noise floor
int muscleThreshold[2];					// muscle threshold value
int sensitivityOffset=0;				// sensitivity of muscle sensor (dist from noise floor), lower = more sensitive (default 100)
int currentGrip = FISTGRIP;				// current grip pattern for muscle sense change
int muscleControlMode=0;				// whether muscle sense is OFF, standard or position
int prevArmDirections[NUM_DIR_SAMPLES];	// muscle direction readings
int currentPos=0;						// position control
int printMuscleFlag = 0;				// flag to print muscle ADC readings
int gripChangeFlag = 0;					

