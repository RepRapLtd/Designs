/*	Backer Hand - Open Hand Project - Open Bionics
*	Author - Olly McBride
*	Date - April 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*/
int rollingAverage(int *inArray, int size, int val)		//calculate rolling average of array
{
	int l;
	long total = 0;
	int result;

	for(l=0; l<size-1; l++)
	{
		inArray[l] = inArray[l+1];
		total += inArray[l];
	}
	inArray[size-1] = val;
	total += val;
	result = total / size;

	return result;
}

void printArray(int* inArray, int arraySize)	// print array over serial
{
	int w;
	for(w=0;w<arraySize;w++)
	{
		Serial.print(w);
		Serial.print(" ");
		(inArray[w]==2)?Serial.println("-"):Serial.println(dirNameString[inArray[w]]);
	}
	Serial.println("****end of array****");
}

void overwriteArray(int* inArray, int arraySize, int val)		// overwrite array with value
{
	int w;
	for(w=0;w<arraySize;w++)
	{
		inArray[w]=val;
	}
}