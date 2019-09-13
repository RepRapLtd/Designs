/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
void fingerControl(int *inArray)		// if array is passed into motor control
{
	fingerControl(valueList[0],valueList[1],valueList[2],valueList[3]);
}

void fingerControl(int fingerNumber, boolean fingerDirection, int stopPos, int fingerSpeed)
{
	finger[fingerNumber].direction = fingerDirection;
	(stopPos==-1)?finger[fingerNumber].position=fingerPositions[fingerDirection]:finger[fingerNumber].position=stopPos;
	(fingerSpeed==-1)?finger[fingerNumber].speed = DEFAULT_SPEED:finger[fingerNumber].speed = fingerSpeed;
}

void stopMotor(int fingerNumber)
{
	finger[fingerNumber].speed=0;
}

void stopMotors(void)				// stop all motors
{
	stopMotor(0);
	stopMotor(1);
	stopMotor(2);
	stopMotor(3);
	stopMotor(4);
}

void fingerPositionControl(void)	// controls motor PWM values based on current and target position using a proportional controller (triggered by interrupt)
{
	signed int currentError, motorSpeed;
	int currentPosition;
	int proportionalOffset  = 200;			// see graph below for explanation
	int motorStopOffset = 10;				// see graph below for explanation
	float m;
	
	(fingerCounter<NUM_OF_FINGERS-1)?fingerCounter++:fingerCounter=0;	// count through each finger at each function call
	currentPosition=analogRead(finger[fingerCounter].pins[SENSE]);	// store motor position to array
	currentError = (signed int) (finger[fingerCounter].position-currentPosition);
	
	m = (float) (finger[fingerCounter].speed/proportionalOffset);	// speed/position line gradient (see graph below for explanation)
	if(currentError>0)motorStopOffset = -motorStopOffset;
	
	// constrain speed
	if(abs(currentError)<motorStopOffset)motorSpeed=0;											// motor dead zone
	else if(abs(currentError)<proportionalOffset)motorSpeed = m*(currentError+motorStopOffset);	// proportional control
	else if(currentError>motorStopOffset)motorSpeed = finger[fingerCounter].speed;			// set speed depending on direction
	else if(currentError<-motorStopOffset)motorSpeed = -finger[fingerCounter].speed;			// set speed depending on direction
	
	motorControl(fingerCounter,motorSpeed);
}

void motorControl(int fingerNumber, signed int motorSpeed)
{
	boolean dir=0;
	if(motorSpeed< -POS_TOLERANCE)		// determine direction
	{
		(motorSpeed<-255)?motorSpeed=255:motorSpeed= -motorSpeed;
		dir = OPEN;
	}
	else if(motorSpeed>POS_TOLERANCE)
	{
		(motorSpeed>255)?motorSpeed=255:motorSpeed;
		dir = CLOSE;
	}
	else motorSpeed=0;

	analogWrite(finger[fingerNumber].pins[dir],motorSpeed);		//write fingerSpeed to one direction pin
	analogWrite(finger[fingerNumber].pins[!dir],0);				//write 0 to other direction pin
}

/*
*							 255| motor speed
*	______________				|
*				  \				|
*				   \			|
*					\			|
*					 \			|
*					  \			|
*					   \		|
*						\		|
*						 \		|					current error
*  _______________________\_____________________________________
* -400							|	   \					 400
*								|		\
*								|		 \
*								|		  \
*								|		   \
*								|		    \
*								|		     \
*								|   		  \
*								|		       \_______________
*							-255|
*
* The above graph shows the reaction output of the proportional controller, where the current
* error is the distance between the current position of the motor and the target position, and
* motor speed is a PWM value from -255 to 255 (the sign is sued to determine direction).
*
* The gradient of the reaction line can be increased/decreased by adjusting the proportional
* offset value within fingerPositionControl(). The motor deadzone is used to prevent the motors
* from buzzing and getting warm.
*/