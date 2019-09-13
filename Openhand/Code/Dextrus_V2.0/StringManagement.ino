/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
void processCommand(void)		// interpret and store received serial commands
{
	// return numbers after char in buffer
	valueList[0] = parsenumber('F',buffer);     // finger number
	valueList[2] = parsenumber('P',buffer);		// stop position
	valueList[3] = parsenumber('S',buffer);     // speed
	gripCmd		 = parsenumber('G',buffer);		// predefined grips
	advancedCmd  = parsenumber('A',buffer);		// advanced control
	muscleCmd	 = parsenumber('M',buffer);		// muscle control
	handCmd		 = parsenumber('H',buffer);		// left or right hand
	demoCmd		 = parsenumber('D',buffer);		// demo mode
	instructionsCmd = parsenumber('?',buffer);	// sends serial instructions

	// direction control
	int dirO = parsenumber('O',buffer);             // OPEN
	int dirC = parsenumber('C',buffer);             // CLOSE
	if(dirO==0)valueList[1]=OPEN;
	else if(dirC==0)valueList[1]=CLOSE;
	else
	{
		if(valueList[0]!=-1)valueList[1] = !finger[valueList[0]].direction;	// toggle finger direction
		else valueList[1] = !currentDir;									// toggle grip direction
	}

	// map the input position from 0-100 to min-max position
	if(valueList[2]!=-1)
	{
		(valueList[2]>100)?valueList[2]=100:valueList[2];
		(valueList[2]<0)?valueList[2]=0:valueList[2];
		valueList[2] = map(valueList[2],0,100,FULLY_CLOSED,FULLY_OPEN);
	}
}

void printCommand(void)		// print interpreted commands over serial
{
	if(valueList[0]!=-1)
	{
		Serial.print("\n");
		Serial.print("Finger ");
		Serial.println(valueList[0]);
		
		Serial.print("Direction ");
		Serial.println(dirNameString[valueList[1]]);

		Serial.print("stopPos ");
		(valueList[2]!=-1)?Serial.println(map(valueList[2],FULLY_CLOSED,FULLY_OPEN,0,100)):Serial.println(map(fingerPositions[valueList[1]],FULLY_CLOSED,FULLY_OPEN,0,100));
		
		Serial.print("Speed ");
		(valueList[3]!=-1)?Serial.println(valueList[3]):Serial.println(DEFAULT_SPEED);
	}
	if(gripCmd!=-1)
	{
		
		Serial.print("Grip ");
		Serial.println(gripNameString[gripCmd]);
		
		Serial.print("Direction ");
		Serial.println(dirNameString[valueList[1]]);
		Serial.print("\n");
	}
	if(instructionsCmd==0)
	{
		printInstructions();
	}
}

float parsenumber(char code,char *ptr)	//search input string and return numbers after char in buffer
{
	float val = -1;		//val returned if no value found for each segment
	while(ptr && *ptr && ptr<buffer+strLength) {
		if(*ptr==code) {
			return atof(ptr+1);
		}
		ptr=strchr(ptr,' ')+1;
	}
	return val;		  //return numbers after char in buffer
}

void clearAll(void)		//clear all input variables for the next string
{
	int i;
	for(i=0;i<=3;i++)
	{
		valueList[i]=-1;
	}
	
	gripCmd=-1;
	advancedCmd=-1;
	muscleCmd=-1;
	instructionsCmd=-1;
	handCmd=-1;
	demoCmd=-1;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void printInstructions(void)
{
	Serial.println("");
	Serial.println("    Open Hand Project Backer Hand Serial Commands");
	Serial.println("_________________________________________________");
	Serial.println("");
	Serial.println("Advanced Settings (A#, ?)");
	Serial.println("Command     Description");
	Serial.println("A0          Turns 'Screensaver Demo Mode' OFF");
	Serial.println("A1          Turns 'Screensaver Demo Mode' ON");
	Serial.println("A2          Turns 'Serial Commands Instructions' OFF");
	Serial.println("A3          Turns 'Serial Commands Instructions' ON");
	Serial.println("A5          Stop all motors");
	Serial.println("?           Display serial commands list");
	Serial.println("");
	Serial.println("Grip Control (G#)");
	Serial.println("Command     Description");
	Serial.println("G0          Fist");
	Serial.println("G1          Palm");
	Serial.println("G2          Thumbs Up");
	Serial.println("G3          Point");
	Serial.println("G4          Pinch");
	Serial.println("G5          Tripod");
	Serial.println("");
	Serial.println("Finger Control (F#, P##, S##)");
	Serial.println("Command     Description");
	Serial.println("F#          Finger, where # is the finger number (F0 - F4)");
	Serial.println("F# P50      Finger # to position 50 (P0 - P100)");
	Serial.println("F# S255     Finger # at speed 255 (S0-S255)");
	Serial.println("");
	Serial.println("Direction (O, C)");
	Serial.println("Command     Description");
	Serial.println("## O        Open, where ## is a Grip or Finger command");
	Serial.println("## C        Close, where ## is a Grip or Finger command");
	Serial.println("");
	Serial.println("Muscle Control (M)");
	Serial.println("Command     Description");
	Serial.println("M0          Muscle control OFF");
	Serial.println("M1          Standard muscle control ON");
	Serial.println("M2          Muscle position control ON");
	Serial.println("M3          Toggle whether to display muscle readings");
	Serial.println("");
	Serial.println("");
	Serial.println("Examples");
	Serial.println("G0 O        Fist Grip Open");
	Serial.println("G2 C        Thumbs Up Close");
	Serial.println("F0 O        Thumb Open");
	Serial.println("F4 P50      Pinky to position 50");
	Serial.println("F1 P50 S80  Index finger to position 50 at speed 80");
	Serial.println("F0 O S200   Thumb Open at speed 200");
	Serial.println("");
	Serial.println("");
}