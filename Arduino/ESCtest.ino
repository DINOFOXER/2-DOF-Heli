#include <Servo.h>
Servo ESC;

void setup() {
ESC.attach(6, 1000, 2000);
ESC.write(0); 
delay(3000); /*é necessário esperar um tempo pro ESC se configurar*/
ESC.write(20); /*130 levanta*/
delay(2000);
ESC.write(0);
}

void loop() {

}
