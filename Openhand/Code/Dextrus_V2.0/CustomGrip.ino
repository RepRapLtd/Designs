/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/

// 3 dimensional array to hold the stop positions for each finger for each grip pattern
// the top group refers to the OPEN finger positions, and the bottom group as the CLOSE finger positions
int gripPositions[2][NUM_OF_GRIPS][NUM_OF_FINGERS] = {
	{	// OPEN POSITIONS
		//Finger 0		Finger 1		Finger 2		Finger 3		Finger 4
		{400,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	// FISTGRIP
		{FULLY_OPEN,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	// PALMGRIP
		{FULLY_OPEN,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// THUMBSUP
		{FULLY_CLOSED,	FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// POINT
		{FULLY_OPEN,	FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// PINCHGRIP
		{FULLY_OPEN,	FULLY_OPEN,		FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED},	// TRIPODGRIP
	},
	{	// CLOSED POSITIONS
		//Finger 0		Finger 1		Finger 2		Finger 3		Finger 4
		{FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// FISTGRIP
		{FULLY_OPEN,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// PALMGRIP
		{FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// THUMBSUP
		{FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// POINT
		{980,			800,			FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	// PINCHGRIP
		{800,			800,			800,			FULLY_CLOSED,	FULLY_CLOSED},	// TRIPODGRIP
	}
};

void gripControl(int desiredGrip, int direction, int speed)
{
	int i;
	currentDir = direction;		// set the target positions of each finger to the preset OPEN/CLOSE positions
	for(i=0;i<NUM_OF_FINGERS;i++){
		finger[i].position=gripPositions[direction][desiredGrip][i];
		// if fingers don't move in grip, use speed of 255, else use muscle controlled speed
		(gripPositions[OPEN][desiredGrip][i]!=gripPositions[CLOSE][desiredGrip][i])?finger[i].speed=speed:finger[i].speed=255;
	}
}

void gripControl(int desiredGrip, int direction)	// if no speed entered
{
	gripControl(desiredGrip,direction,DEFAULT_SPEED);
}

void gripControl(int desiredGrip)	// if no direction or speed entered
{
	gripControl(desiredGrip,!currentDir,DEFAULT_SPEED);
}

void gripMovement(int desiredGrip, int position, int speed)		// used when moving hand incrementally (muscle position control)
{
	int i;
	for(i=0;i<NUM_OF_FINGERS;i++)
	{
		finger[i].position=map(position,0,100,gripPositions[CLOSE][desiredGrip][i],gripPositions[OPEN][desiredGrip][i]);
		//if fingers don't move in grip, use speed of 255, else use muscle controlled speed
		(gripPositions[OPEN][desiredGrip][i]!=gripPositions[CLOSE][desiredGrip][i])?finger[i].speed=speed:finger[i].speed=255;
	}
}
