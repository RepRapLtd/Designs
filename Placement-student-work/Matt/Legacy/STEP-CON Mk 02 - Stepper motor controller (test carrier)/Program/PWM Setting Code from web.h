 // Update the 'ticklet' count     
 g_ticklet += (256 / TICKLETS);     // Update PWM outputs     
 if((g_pwmout[0]>0)&&(g_ticklet<=g_pwmout[0]))       pinHigh(SPWM_PIN0);     else       pinLow(SPWM_PIN0);


/*The output is a nice stable PWM signal at close to 60Hz [≈ electromagnetic — standard AC mains power, American AC, Osaka AC] as shown in the trace to the right. The library uses #define statements in hardware.h to specify the number of PWM channels to enable and to assign each one to an output pin.

Although you could theoretically use all 6 IO pins as PWM outputs using this method I've imposed an upper limit of 4 pins in the implementation. This can easily be extended if needed.

A typical set up (in this case for 3 PWM outputs on B0, B1 and B2) looks like this:*/

    #define SOFTPWM_ENABLED

     /** Use 3 PWM channels */
    #define SPWM_COUNT 3

     /** Pin associated with SPWM0 */
    #define SPWM_PIN0 PINB0

     /** Pin associated with SPWM1 */
    #define SPWM_PIN1 PINB1

     /** Pin associated with SPWM2 */
    #define SPWM_PIN2 PINB2

 /*You can use both the hardware PWM and software PWM side by side. The software implementation is useful for controlling LED's while the hardware PWM can be used to control motors or servos.


Using the software PWM output to control an RGB LED is straight forward. You will need three channels as shown above (one each for the red, green and blue elements of the LED). I run my ATtiny from a 3.3V source which is not enough to drive a blue LED (they typically have a forward voltage drop of over 3V) so I drive the LED's from a separate 5V supply through a 2N7000 FET. This also has the advantage of minimising the current being pulled through the output pins of the ATtiny (20mA per LED which means 60mA if they are all on simultaneously).

 The sample code below transitions the LED from red to green to blue and back again: */
 static uint8_t g_red = 0;     
 static uint8_t g_grn = 0;     
 static uint8_t g_blu = 0;

 /** Set the target values for the LED's      *     
	* @param red target for red LED      
	* @param grn target for green LED      
	* @param blu target for blue LED      */   
	
 static void ledSet(uint8_t red, uint8_t grn, uint8_t blu) {       
	g_red = red;       
	g_grn = grn;       
	g_blu = blu;       
	}

 /** Update the current PWM values to bring them closer to the target      */     
 static void ledUpdate() 
 {       
	// Update RED value       
	uint8_t val = spwmValue(SPWM0);       
	if(val<g_red)         val++;       else if(val>g_red)         val--;       spwmOut(SPWM0, val);       
	// Update GREEN value       
	val = spwmValue(SPWM1);       if(val<g_grn)         val++;       else if(val>g_grn)         val--;       spwmOut(SPWM1, val);       
	// Update BLUE value       
	val = spwmValue(SPWM2);       if(val<g_blu)         val++;       else if(val>g_blu)         val--;       spwmOut(SPWM2, val);       
	}

 static bool ledMatch() {       
	return ((spwmValue(SPWM0)==g_red)&&(spwmValue(SPWM1)==g_grn)&&(spwmValue(SPWM2)==g_blu));       
	}

 //---------------------------------------------------------------------------     // Main program     //---------------------------------------------------------------------------

 /** Program entry point      */     
 void main() {       
	spwmInit();       
	sei();       
	// Set up output values       
	uint32_t output = 0x00FF0000L;       
	ledSet((output>>16)&0xFF, (output>>8)&0xFF, output&0xFF);       
	while(true) {         
		if(ledMatch()) {
			output = output >> 8;           
			if(output==0)             
				output = 0x00FF0000L;           
				ledSet((output>>16)&0xFF, (output>>8)&0xFF, output&0xFF);           
				}         
		ledUpdate();         
		wait(10);         
		}       
	}