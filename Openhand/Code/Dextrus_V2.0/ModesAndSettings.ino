/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
void advancedSettings(void)
{
	if(advancedCmd!=-1)
	{
		switch(advancedCmd)
		{
			case 0:
			EEPROM.write(demoFlagLoc,0);				// demo mode toggled off
			demoOnce = 0;
			Serial.println("Automatic demo mode toggled off");
			break;
			case 1:
			EEPROM.write(demoFlagLoc,1);				// demo mode toggled on
			Serial.println("Automatic demo mode toggled on");
			break;
			case 2:
			EEPROM.write(instructionsFlagLoc,0);		// initial instructions toggled off
			Serial.println("Initial serial instructions toggled off");
			break;
			case 3:
			EEPROM.write(instructionsFlagLoc,1);		// initial instructions toggled on
			Serial.println("Initial serial instructions toggled on");
			printInstructions();
			break;
			case 5:
			stopMotors();
			Serial.println("Stop Motors");
			break;
		}
	}
	if(muscleCmd!= -1)
	{
		switch(muscleCmd)
		{
			case 0:							// muscle control off
			muscleControlMode = 0;
			Serial.println("Muscle control OFF ");
			break;
			case 1:							// standard muscle control
			muscleControlMode = 1;
			Serial.println("Standard muscle control ON");
			break;
			case 2:							// position muscle control
			muscleControlMode = 2;
			Serial.println("Muscle position control ON");
			break;
			case 3:
			if(muscleControlMode!=0)
			{
				printMuscleFlag = !printMuscleFlag;
				Serial.print("Display muscle readings ");
				Serial.println(dirNameString[printMuscleFlag+2]);			// print ON/OFF
			}
			break;
			case 4:
			if(muscleControlMode!=0)
			{
				gripChangeFlag = !gripChangeFlag;
				Serial.print("Grip Change Mode ");
				Serial.println(dirNameString[gripChangeFlag+2]);			// print ON/OFF
				EEPROM.write(gripChangeFlagLoc,gripChangeFlag);
			}
			break;
			
		}
		EEPROM.write(muscleModeFlagLoc,muscleControlMode);
	}
	if(handCmd!= -1)
	{
		if(handCmd!= 0)
		{
			EEPROM.write(handIsFlagLoc,handCmd);		// set EEPROM to RIGHT or LEFT
			setupFingerPins();							// reconfigure finger pins
		}
		Serial.print("Hand is ");
		Serial.println(dirNameString[EEPROM.read(handIsFlagLoc)+3]);	// print which hand is entered
	}
	if(demoCmd==0)
	{
		Serial.println("Demo Mode");
		demoOnce=1;
	}
}

void demoMode(void)		// demo mode
{
	if(demoModeCounter==0)
	{
		Serial.println(" ");
		Serial.println("Demo Mode");
		Serial.print("This mode starts automatically after ");
		Serial.print(demoModeInnactivityTime);
		Serial.println("s of inactivity");
		Serial.println("Enter command 'A0' to disable the automatic demo mode");
		Serial.println(" ");
	}
	demo();
	demoModeCounter++;
	if(demoModeCounter>=(NUM_OF_GRIPS*2))
	{
		demoOnce=0;
		demoModeCounter=0;
		inactivityCounter=0;
		Serial.println("Fist Grip");
		Serial.println("Direction Open");
		gripControl(FISTGRIP,OPEN);
	}
}

void demo(void)
{
	int k, h;
	
	h = demoModeCounter%2;	// checks to see if grip is odd or even
	k = demoModeCounter/2;	// gets demo grip
	
	(!h)?h=OPEN:h=CLOSE;	// if even, OPEN, else CLOSE
	
	gripControl(k,h);		// perform grip
	Serial.print("Grip ");	// print grip details
	Serial.println(gripNameString[k]);
	Serial.print("Direction ");
	Serial.println(dirNameString[h]);
	delay(demoGripDuration);
}

void setDefaults(void)
{
	int i,j;
	// set all fingers to be fully open
	currentGrip = FISTGRIP;
	for(i=0;i<NUM_OF_FINGERS;i++){
		finger[i].position=gripPositions[OPEN][currentGrip][i];
		finger[i].speed=DEFAULT_SPEED;
	}
	currentPos=FULLY_OPEN;
	
	// set previous muscle signal directions and peaks to be falling
	for(i=0;i<=1;i++)
	{
		prevSignalDir[i]=0;		// previous signal direction
		for(j=0;j<NUM_PEAKS;j++)
		{
			prevPeaks[i][j] = DEFAULT_PEAKS;	// set default peaks
		}
	}
	
	// turn ON/OFF muscle control & gripChangeMode at start up
	muscleControlMode = EEPROM.read(muscleModeFlagLoc);
	gripChangeFlag = EEPROM.read(gripChangeFlagLoc);
	switch(muscleControlMode)
	{
		case 1:							// standard muscle control
		muscleControlMode = 1;
		Serial.println("Standard muscle control ON");
		break;
		case 2:							// position muscle control
		muscleControlMode = 2;
		Serial.println("Muscle position control ON");
		break;
		default:
		break;
	}
}

void initialEEPROMconfig(void)	// write default flag values to EEPROM
{
	EEPROM.write(demoFlagLoc,ON);
	EEPROM.write(instructionsFlagLoc,ON);
	EEPROM.write(handIsFlagLoc,RIGHT);
	EEPROM.write(muscleModeFlagLoc,OFF);
	EEPROM.write(gripChangeFlagLoc,ON);
	
	EEPROM.write(initConfigFlagLoc,8);	// set flag to value to signal config complete
}