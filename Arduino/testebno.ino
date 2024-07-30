#include <Wire.h>

uint8_t pitch_msb;
uint8_t pitch_lsb;

uint8_t yaw_msb;
uint8_t yaw_lsb;

int16_t pitchAngle;
int16_t yawAngle;


void setup() {
 Wire.begin();
 Serial.begin(9600);

 Wire.beginTransmission(0x28); //clk source
 Wire.write(0x3F);
 Wire.write(0x00);
 Wire.endTransmission();

 Wire.beginTransmission(0x28); //unidades
 Wire.write(0x3B);
 Wire.write(0x00);
 Wire.endTransmission();

 Wire.beginTransmission(0x28); // temp spurce
 Wire.write(0x40);
 Wire.write(0x00);
 Wire.endTransmission();

 Wire.beginTransmission(0x28); //operation mode
 Wire.write(0x3D);
 Wire.write(0x0C);
 Wire.endTransmission();
 
 delay(100);
}

void loop() {
/* Wire.beginTransmission(0x28);
 Wire.write(0x1F);
 Wire.endTransmission();
 Wire.requestFrom(0x28, 1);
 msb = Wire.read();*/
 
 Wire.beginTransmission(0x28);
 Wire.write(0x1E);
 Wire.endTransmission();
 Wire.requestFrom(0x28, 2);
 pitch_lsb = Wire.read();
 pitch_msb = Wire.read();

 Wire.beginTransmission(0x28);
 Wire.write(0x1A);
 Wire.endTransmission();
 Wire.requestFrom(0x28, 2);
 yaw_lsb = Wire.read();
 yaw_msb = Wire.read();
 
 pitchAngle = pitch_msb << 8 | pitch_lsb;
 yawAngle = yaw_msb << 8 | yaw_lsb;

 Serial.print("Pitch: ");
 Serial.println(pitchAngle/16, DEC);
 Serial.print("Yaw: ");
 Serial.println(yawAngle/16, DEC);
 delay(100);
}
