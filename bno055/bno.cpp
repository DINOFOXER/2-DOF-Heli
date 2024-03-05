
/* In Power Modes (3.2), it is said that the BNO055 will start in Power Mode "Normal", so we don't need do change values in the 0x3E register.
What we need to do after start-up is configure the Operation Mode (3.3). The way to do so is by changing values in the 0x3D register (OPR_MODE).
Since we're looking for precision, the code will activate the fusion mode NDOF (table 3.5). Also, it is necessary to wait 7 ms to change from
CONFIG mode to NDOF mode. Section 3.6.1 tells us how to select units of measurement
*/


#include <iostream>
#include "pigpio.h"

using namespace std;

#define xDegH = 0x1B
#define xDegL = 0x1A
#define bno = 0x29

int handle = 0;
int16_t xDegree = 0;

int main (){

	gpioInitialise();
	handle = i2cOpen(1, bno, 0); /* creating handle and starting communication with BNO */
  i2cWriteByteData(handle, 0x3B, 0x00); /* Units: m/s2, dps, degrees, Celsius */
  i2cWriteByteData(handle, 0x3D, 0x0C); /* activating NDOF mode */
  time_sleep(0.01); /* time needed to switch modes from CONFIG */

  i2cClose(handle);
  gpioTerminate();

  return 0;
}
