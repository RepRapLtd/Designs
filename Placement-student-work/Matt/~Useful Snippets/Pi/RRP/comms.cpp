#include "comms.h"

const int slave = 8;
int fd = -1;



char GetSlaveByte()
{
	if(fd < 0)
	{
		cout << "I2C not initialised." << endl;
		return 0;
	}
        int result = wiringPiI2CRead (fd);
        if(result < 0)
	{
		cout << strerror(result) << endl;
		return 0;
	}
	return (char)result;
}

int main ()
{
  fd = wiringPiI2CSetup (slave) ;
  if(fd < 0)
  {
	cout << strerror(fd) << endl;
	return 1;
  }

   char c;
   for(;;)
   {
       if(c = GetSlaveByte())
        {
              cout << c;
        }
  

	cin.get(c);
          wiringPiI2CWrite (fd, c);
	
  } 
  return 0;
}
