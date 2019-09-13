/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
void muscleControl(void)
{
	int muscleState[2];		// OPEN/CLOSE for each muscle
	int armDir;				// direction of overall arm (OPEN/CLOSE/NONE)
	int setHandPos = 0;		// position of hand
	int setHandSpeed = 0;	// speed of hand movement
	int getHandPos;			// reads 'fingerToRead' to determine hand position (only change grip when OPEN)
	int fingerToRead;		// finger that moves in each grip, used to read hand pos (index for all apart from thumbs up)
	
	// read muscles, if above threshold return error (measured - threshold), if below threshold return 0
	muscleState[0] = readMuscle(0);
	muscleState[1] = readMuscle(1);

	if(printMuscleFlag)		// if flag is set, print raw ADC values
	{
		Serial.print("M0 = ");
		Serial.print(muscleReadings[0][NUM_SAMPLES-1]);
		Serial.print("  T0 = ");
		Serial.print(muscleThreshold[0]);
		Serial.print("      M1 = ");
		Serial.print(muscleReadings[1][NUM_SAMPLES-1]);
		Serial.print("  T1 = ");
		Serial.println(muscleThreshold[1]);
	}

	// store overall direction in FIFO array
	if(muscleState[0]>muscleState[1])rollingAverage(prevArmDirections,NUM_DIR_SAMPLES,OPEN);		// if OPEN
	else if(muscleState[1]>muscleState[0])rollingAverage(prevArmDirections,NUM_DIR_SAMPLES,CLOSE);	// if CLOSE
	else rollingAverage(prevArmDirections,NUM_DIR_SAMPLES,2);										// else NONE
	
	// print array of previous arm directions
	//printArray(prevArmDirections,NUM_DIR_SAMPLES);
	
	// determine which finger moves in each grip (index finger for all grips apart from thumbs up)
	(currentGrip==THUMBSUP)?fingerToRead=0:fingerToRead=1;
	cli();// stop interrupts
	getHandPos = analogRead(finger[fingerToRead].pins[SENSE]);
	sei();// allow interrupts
	
	if(gripChangeFlag)	// check for grip change if flag is set
	{
		if(gripChange()&&((abs(getHandPos-gripPositions[OPEN][currentGrip][fingerToRead])<50)||(currentDir==OPEN)))   // if double tap and in the open position		
		{
			Serial.println("Grip Change");
			(currentGrip<NUM_OF_GRIPS-1)?currentGrip++:currentGrip=0;		// change grip
			overwriteArray(prevArmDirections,NUM_DIR_SAMPLES,NONE);			// overwrite array to stop changing grips constantly
			prevArmDirections[NUM_DIR_SAMPLES-1]=OPEN;
			currentDir=CLOSE;
			Serial.print("Grip ");
			Serial.println(gripNameString[currentGrip]);
		}
	}

	if(muscleControlMode==1)		// standard muscle control
	{
		if((prevArmDirections[NUM_DIR_SAMPLES-1]==OPEN)&&(currentDir!=OPEN))	// if OPEN
		{
			Serial.println("Arm OPEN");
			currentPos=FULLY_OPEN;
			gripControl(currentGrip,OPEN);	
		}
		else if((prevArmDirections[NUM_DIR_SAMPLES-1]==CLOSE)&&(currentDir!=CLOSE))	// if CLOSE
		{
			Serial.println("Arm CLOSE");
			currentPos=FULLY_CLOSED;
			gripControl(currentGrip,CLOSE);
		}
	}
	else if(muscleControlMode==2)	// position muscle control
	{
		setHandPos = musclePosControl(prevArmDirections,NUM_DIR_SAMPLES);	// determine muscle position		
		//setHandSpeed = muscleSpeedControl(muscleState);					// determine muscle speed 	
		setHandSpeed = 200;
		gripMovement(currentGrip,setHandPos,setHandSpeed);		
	}
}

int readMuscle(int muscleNum)		// reads a muscle sensor, stores in rolling buffer, stores average in noiseFloor			(muscleReadings[muscleNum][NUM_SAMPLES-1] is current reading)
{
	int muscleValue;
	int deltaValue=0;
	
	// read muscle pin
	cli();// stop interrupts
	muscleValue = analogRead(musclePinList[muscleNum]);
	sei();// allow interrupts
	// if muscle value is less than noise floor + NOISE_OFFSET, add value to FIFO muscleReadings array, store average in noiseFloor
	if(muscleValue<(noiseFloor[muscleNum]+NOISE_OFFSET))
	{
		noiseFloor[muscleNum] = rollingAverage(muscleReadings[muscleNum],NUM_SAMPLES,muscleValue);
	}

	// if current reading is greater than the noise floor + sensitivityOffset, generate new threshold
	if(muscleReadings[muscleNum][NUM_SAMPLES-1]>(noiseFloor[muscleNum]+sensitivityOffset))
	{
		muscleThreshold[muscleNum] = updateThreshold(muscleNum);
	}
	
	// if above threshold return error (measured - threshold), if below threshold return 0
	deltaValue = muscleReadings[muscleNum][NUM_SAMPLES-1]-muscleThreshold[muscleNum];
	
	if(deltaValue>0)return deltaValue;
	else return 0; 	
}

int updateThreshold(int muscleNum)		// return threshold of (peakAverage-noiseFloor)/2 + noiseFloor
{
	int currentSignalDir=0;
	
	// set flag depending on signal direction, if current reading is greater than previous reading then RISING, else FALLING
	muscleReadings[muscleNum][NUM_SAMPLES-1]>muscleReadings[muscleNum][NUM_SAMPLES-2]?currentSignalDir=1:currentSignalDir=0;		// 1 = RISING,   0 = FALLING
		
	// if signal reaches peak, store current peak in FIFO array of previous peaks and calculate rolling average
	if((prevSignalDir[muscleNum]==1)&&(currentSignalDir==0))		// 1 = RISING,   0 = FALLING
	{
		peakAverage[muscleNum] = rollingAverage(prevPeaks[muscleNum],NUM_PEAKS,muscleReadings[muscleNum][NUM_SAMPLES-2]);
	}
	
	// remember the direction of the signal, either rising or falling
	prevSignalDir[muscleNum]=currentSignalDir;
	
	// return dynamic threshold value
	return ((peakAverage[muscleNum]-noiseFloor[muscleNum])/2)+noiseFloor[muscleNum];
}

int gripChange(void)			// search through prevArmDir array, if grip change detected return 1, else return 0
{
	int arrayPos;		 // position within array
	int moreThan = 160;	 // number of directions in each sections to count as a double tap
	int dirVal = OPEN;   // direction sequence to search for/match with
	int dirCount = 0;    // number of directions in each section
	
	for(arrayPos=NUM_DIR_SAMPLES-1;arrayPos>=0;arrayPos--)          // count backwards through array
	{
		if(prevArmDirections[arrayPos]==dirVal)        // if element is desired dir, increment dir counter
		{
			dirCount++;
		}
		else         // if not next desired dir or next desired dir but number of current dir < morethan, break
		{
			break;
		}
	}
	
	// if grip change detected, return 1, else return 0
	if(dirCount>=moreThan)return 1;
	else return 0;
}

int musclePosControl(int* inArray,int arraySize)	// change position of hand when muscles active
{
	currentDir=CLOSE;
	int position = currentPos;

	if((inArray[arraySize-1]==OPEN)&&(inArray[arraySize-2]==OPEN))					// if muscle OPEN
	{
			position+=MUSCLE_POS_INCREMENT;		// decrement position in OPEN direction
			//Serial.println("OPENING");		
	}
	else if((inArray[arraySize-1]==CLOSE)&&(inArray[arraySize-2]==CLOSE))			// if muscle CLOSE
	{
		position-=MUSCLE_POS_INCREMENT;
		//Serial.println("CLOSING");				// increment position in CLOSE direction
	}
	
	position = constrain(position,0,100);	// set limits
	currentPos = position;
	
	return position;
}

int muscleSpeedControl (int* inArray)		// proportional muscle speed control	
{
	int muscleNum;
	
	if(inArray[0]>inArray[1])
	{
		muscleNum = 0;
	}
	else muscleNum = 1;
	
	return map(inArray[muscleNum],0,peakAverage[muscleNum],50,255);
}

/*int muscleSpeedControl (int* inArray)		//proportional muscle speed control	
{
	float speedThresh = 0.80;
	int muscleNum;
	int speed;
	
	if(inArray[0]>inArray[1])
	{
		muscleNum = 0;
	}
	else 
	{
		muscleNum = 1;
	}

	if(inArray[muscleNum] > ((maximum(prevPeaks[muscleNum],NUM_PEAKS)-muscleThreshold[muscleNum])*speedThresh))
	{
		return 255;
	}
	else
	{
		return 100;
	}
}*/

