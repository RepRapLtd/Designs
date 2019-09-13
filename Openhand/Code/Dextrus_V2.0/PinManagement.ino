/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/

void setupFingerPins(void)   // assign pins for each finger, store pins within list and set as INPUT/OUTPUT
{
	assignPins();
	setPinDirection();
}
	
void assignPins(void)
{
	switch(EEPROM.read(handIsFlagLoc))
	{
		case RIGHT:
		//RIGHT HAND
		finger[FINGER0].pins[DIR1]=5;         // finger0 (thumb)	dir1
		finger[FINGER0].pins[DIR2]=2;         // finger0 (thumb)	dir2
		finger[FINGER0].pins[SENSE]=A0;       // finger0 (thumb)	sense
		
		finger[FINGER1].pins[DIR1]=3;         // finger1 (index)	dir1
		finger[FINGER1].pins[DIR2]=6;         // finger1 (index)	dir2
		finger[FINGER1].pins[SENSE]=A1;       // finger1 (index)	sense
		
		finger[FINGER2].pins[DIR1]=7;         // finger2 (middle) dir1
		finger[FINGER2].pins[DIR2]=8;         // finger2 (middle) dir2
		finger[FINGER2].pins[SENSE]=A2;       // finger2 (middle) sense
		
		finger[FINGER3].pins[DIR1]=10;        // finger3 (ring)	dir1
		finger[FINGER3].pins[DIR2]=9;		  // finger3 (ring)	dir2
		finger[FINGER3].pins[SENSE]=A3;       // finger3 (ring)	sense
		
		finger[FINGER4].pins[DIR1]=11;        // finger4 (pinky)	dir1
		finger[FINGER4].pins[DIR2]=12;        // finger4 (pinky)	dir2
		finger[FINGER4].pins[SENSE]=A4;       // finger4 (pinky)	sense
		break;
		case LEFT:
		//LEFT HAND
		finger[FINGER0].pins[DIR1]=5;         // finger0 (thumb)	dir1
		finger[FINGER0].pins[DIR2]=2;         // finger0 (thumb)	dir2
		finger[FINGER0].pins[SENSE]=A0;       // finger0 (thumb)	sense
				
		finger[FINGER1].pins[DIR1]=11;         // finger1 (index)	dir1
		finger[FINGER1].pins[DIR2]=12;         // finger1 (index)	dir2
		finger[FINGER1].pins[SENSE]=A4;       // finger1 (index)	sense
				
		finger[FINGER2].pins[DIR1]=10;         // finger2 (middle) dir1
		finger[FINGER2].pins[DIR2]=9;         // finger2 (middle) dir2
		finger[FINGER2].pins[SENSE]=A3;       // finger2 (middle) sense
				
		finger[FINGER3].pins[DIR1]=7;        // finger3 (ring)	dir1
		finger[FINGER3].pins[DIR2]=8;			// finger3 (ring)	dir2
		finger[FINGER3].pins[SENSE]=A2;       // finger3 (ring)	sense
				
		finger[FINGER4].pins[DIR1]=3;        // finger4 (pinky)	dir1
		finger[FINGER4].pins[DIR2]=6;        // finger4 (pinky)	dir2
		finger[FINGER4].pins[SENSE]=A1;       // finger4 (pinky)	sense
		break;
	}
	
	musclePinList[0]=A6;			//muscle1 sense ADC pin
	musclePinList[1]=A7;			//muscle2 sense ADC pin
}	

void setPinDirection(void)
{
	int i;
	// count through each finger, setting pins to INPUT and OUTPUT
	for(i=0;i<NUM_OF_FINGERS;i++)					// count through finger pins
	{
		pinMode(finger[i].pins[DIR1],OUTPUT);		// set dir1 as OUTPUT
		pinMode(finger[i].pins[DIR2],OUTPUT);		// set dir2 as OUTPUT
		pinMode(finger[i].pins[SENSE],INPUT);		// set sense as INPUT
	}
	pinMode(musclePinList[0],INPUT);				// set muscle pins as INPUT
	pinMode(musclePinList[1],INPUT);				// set muscle pins as INPUT
}
