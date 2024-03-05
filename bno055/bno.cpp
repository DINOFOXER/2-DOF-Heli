#include <iostream>
#include "pigpio.h"

using namespace std;

#define xDegH = 0x1B
#define xDegL = 0x1A
#define bno = 0x29

int handle = 0;
int16_t xDegree = 0;



int main () {

	gpioInitialise();
  handle = i2cOpen(1, bno, 0);

  i2cClose(handle);
  gpioTerminate();
  return 0;
}
	
	
