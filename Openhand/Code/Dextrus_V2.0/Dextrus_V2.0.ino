/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*	
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
#include "Globals.h"
#include <EEPROM.h>

void setup()
{
	//User adjustable parameters
	sensitivityOffset = 100;			// sensitivity of muscle sensor (dist from noise floor), lower = more sensitive (default 100)
	demoModeInnactivityTime = 5;		// number of seconds of inactivity before demo mode screen saver activates
	
	Serial.begin(38400);				// start serial
	Serial.println("Open Hand Project - Backer Hand");
	setupFingerPins();					// assign pins for each finger, store pins within list and set as INPUT/OUTPUT
	timerSetup();						// start timer interrupts
	clearAll();							// set all serial/command buffer variables to -1

	setDefaults();		// initialise buffers, finger positions and muscle control
	
	delay(1000);
	
	if(EEPROM.read(initConfigFlagLoc)!=8)initialEEPROMconfig();		// if running for the first time, write default values to EEPROM
	if(EEPROM.read(instructionsFlagLoc))printInstructions();		// if instructions not turned off, print initial instructions
	if(EEPROM.read(demoFlagLoc))demoOnce=1;							// if EEPROM flag is set, run demo mode once
}

void loop()
{
	// interpret incoming Serial commands
	while(Serial.available() > 0)	// if something is available
	{
		inactivityCounter=0;			// if Serial is received, reset inactivity/prevent demo mode
		char c=Serial.read();			// receive Serial
		Serial.print(c);				// repeat it back so I know you got the message
		if(strLength<MAX_BUF) buffer[strLength++]=c;  // store it
		if(c==13) {						// if entire message received
			Serial.print("\n");
			buffer[strLength]=0;		// end the buffer so string functions work right
			processCommand();			// separate string to command variables
			strLength=0;				// clear input buffer
		}
	}
	printCommand();						// print received and interpreted command
	advancedSettings();					// toggle demo & muscle mode on/off

	if(muscleControlMode>0)muscleControl();						// muscle control flag
	if(valueList[0]!=-1)fingerControl(valueList);				// finger control
	if(gripCmd!=-1)gripControl(gripCmd,valueList[1]);			// grip control
	if(inactivityCounter>=demoModeInnactivityTime)demoMode();	// timer only counts if EEPROM flag enabled
	
	clearAll();					// clear all serial command buffers
}

