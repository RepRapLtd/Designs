/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
int milliSecondCounter = 0;			//inactivity timer
int fingerPosCounter=0;

void timerSetup(void)			
{									
	cli();//stop interrupts
	
	/* Timer 1 at 10Hz every 100mS for muscle sense
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1  = 0;//initialize counter value to 0
	// set compare match register for 10hz increments
	OCR1A = 24999;// = (16*10^6) / (64 * 10) - 1	
	// turn on CTC mode
	TCCR1A |= (1 << WGM12);
	// Set CS11 bit for 64 prescaler
	TCCR1B |= (1 << CS11) | (1 << CS10); 
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);	//*/
	
	/* Timer 5 at 1kHz every 1mS for inactivity/demo mode timer*/
	TCCR5A = 0;// set entire TCCR5A register to 0      
	TCCR5B = 0;// same for TCCR5B
	TCNT5  = 0;//initialize counter value to 0
	// set compare match register for 1khz increments
	OCR5A = 4000;// = (16*10^6) / (1000) - 1		1kHz = 1999
	// turn on CTC mode
	TCCR5A |= (1 << WGM51);
	// Set CS51 bit for 8 prescaler
	TCCR5B |= (1 << CS51);
	// enable timer compare interrupt
	TIMSK5 |= (1 << OCIE5A);	//*/


	sei();//allow interrupts
}

/* Timer 5 at 1kHz every 1mS for inactivity/demo mode timer*/
ISR(TIMER5_COMPA_vect)		
{
	sei();		// allow interrupts to interrupt this interrupt
	milliSecondCounter++;
	if(milliSecondCounter>2000)				// every 1s, increment inactivity counter
	{
		milliSecondCounter=0;
		if(demoOnce)inactivityCounter++;
	}
	fingerPosCounter++;
	if(fingerPosCounter>2)
	{
		fingerPosCounter=0;
		fingerPositionControl();
	}
} 


