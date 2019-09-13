/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
#ifndef _GLOBALS_h
#define _GLOBALS_h

/* HAND TYPE */
#define RIGHT	1
#define LEFT	2
/* PINS */
#define NUM_OF_CTRLPINS	3
#define DIR1	0
#define DIR2	1
#define SENSE	2
/* DIRECTIONS */
#define OPEN		0	// hand
#define CLOSE		1	// hand
#define NONE		2	// hand
#define FALLING		0	// muscle signal
#define RISING		1	// muscle signal
#define OFF			0	// EEPROM flag
#define ON			1	// EEPROM flag
/* FINGERS */
#define NUM_OF_FINGERS	5
#define FINGER0		0		// thumb	flex
#define FINGER1		1		// index flex
#define FINGER2		2		// middle flex
#define FINGER3		3		// ring flex
#define FINGER4		4		// pinky flex
/* GRIPS */
#define NUM_OF_GRIPS	6
#define FISTGRIP		0
#define PALMGRIP		1
#define THUMBSUP		2
#define POINTGRIP		3
#define PINCHGRIP		4
#define TRIPODGRIP		5
/* EEPROM FLAGS */
#define initConfigFlagLoc	0	// if not set, write default flag values to EEPROM
#define demoFlagLoc			1	// if demo mode runs at startup
#define instructionsFlagLoc	2	// if serial instructions show at startup
#define handIsFlagLoc		3	// whether had is LEFT or RIGHT
#define muscleModeFlagLoc	4	// whether muscle control is ON/OFF at startup
#define gripChangeFlagLoc	5	// whether gripChange() is enabled/disabled
/* DEFAULTS */
#define FULLY_OPEN		75		// fully open position for the hand
#define FULLY_CLOSED	910		// fully closed position for the hand
#define DEFAULT_SPEED	255		// default speed for finger movement
#define POS_TOLERANCE	50		// allowable difference between current finger position and target finger position
#define MAX_BUF			64		// maximum size of Serial incoming buffer
/* MUSCLE CONTROL */
#define NUM_SAMPLES				500		// size of muscle readings buffer
#define NUM_PEAKS				8		// size of previous peaks buffer
#define DEFAULT_PEAKS			900		// initial value to be loaded into buffer
#define NUM_DIR_SAMPLES			200		// size of previous arm movements buffer
#define MUSCLE_POS_INCREMENT	2		// distance to move when using muscle position control
#define NOISE_OFFSET			300		// don't include any value greater than noise floor + NOISE_OFFSET

/* FINGER MOTORS*/
struct fingerType
{
	int position;				// motor target position
	int speed ;					// motor speed
	int direction;				// current motor direction
	int pins[NUM_OF_CTRLPINS];	// pins for each finger (PWM1, PWM2, POS_SENSE)
};
extern struct fingerType finger[NUM_OF_FINGERS];
/* DEMO MODE */
extern int inactivityCounter;		// amount of time the hand has been inactive for, used for demo mode
extern int demoModeInnactivityTime;	// number of seconds of inactivity for demo mode screen saver
extern int demoModeCounter;			// counts through grips of demo mode
extern int demoGripDuration;		// amount of time each grip runs in demo mode (in milliseconds)
extern int demoOnce;
/* SERIAL CONTROL */
extern char buffer[MAX_BUF];	// buffer and variable to store incoming Serial string
extern int strLength;			// how much is in the buffer
// holds the command received over serial
extern int valueList[4];		// string tokens (finger,direction,stop thresh,speed)
extern int advancedCmd;
extern int instructionsCmd;
extern int muscleCmd;
extern int gripCmd;
extern int handCmd;
extern int demoCmd;
/* TEXT STRINGS */
extern char* dirNameString[];	// directions
extern char* gripNameString[];	// grip names
/* FINGERS */
extern int currentDir;
extern int fingerPositions[2];
extern int fingerCounter;
/* Muscle sensing */
extern int musclePinList[2];				// muscle sense ADC pin names
extern int muscleReadings[2][NUM_SAMPLES];	// all muscle readings
extern int prevSignalDir[2];				// previous signal direction
extern int prevPeaks[2][NUM_PEAKS];			// all peak readings
extern int peakAverage[2];					// average of peaks to calculate threshold value
extern int noiseFloor[2];					// average noise floor
extern int muscleThreshold[2];				// muscle threshold value
extern int sensitivityOffset;				// sensitivity of muscle sensor (dist from noise floor), lower = more sensitive (default 100)
extern int currentGrip;						// current grip pattern for muscle sense change
extern int muscleControlMode;				// whether muscle sense is OFF, standard or position
extern int prevArmDirections[NUM_DIR_SAMPLES];	// muscle direction readings
extern int currentPos;						// position control
extern int printMuscleFlag;					// flag to print muscle ADC readings
extern int gripChangeFlag;					// flag to enable/disable gripChange

#endif

