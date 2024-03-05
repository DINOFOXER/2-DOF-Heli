#include <iostream>
#include "pigpio.h"

using namespace std;

int main() {
	gpioInitialise();
	gpioSetMode(17, PI_OUTPUT);
	
	cout << "Ligando motor..." << endl;
	gpioServo(17, 1000);
	time_sleep(5);
	
	cout << "Acelerando motor" << endl;
	gpioServo(17, 1500);
	time_sleep(2);
	
	cout << "Desligando motor...." << endl;
	gpioServo(17, 1000);
	time_sleep(1);
	
	
	gpioTerminate();
	return 0;	
}
