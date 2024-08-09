#include <Wire.h>
#include <Servo.h>

/* Euler angles variables */
uint8_t pitch_msb;
uint8_t pitch_lsb;

uint8_t yaw_msb;
uint8_t yaw_lsb;

float pitchAngle;
float yawAngle;

/* PID variables */
float pitchTarget = 0.0; 
float pitchError = 0.0;
float pitchPrevError = 0.0; 
float pitchPrevIterm = 0.0;

float yawTarget; 
float yawError;
float yawPrevError; 
float yawPrevIterm;

float p_pitch_const = 3.0;   /* Increases responsiveness. Too much makes it oscilate and overcorrect */ 
float i_pitch_const = 0.05;   /* Stops drifting. Too much makes it unresponsive */
float d_pitch_const = 0.5; /* Reduces oscilations. Too much makes it unresponsive */

float p_yaw_const = 2;
float i_yaw_const = 2;
float d_yaw_const = 0.03;

float p_pitch_term, i_pitch_term, d_pitch_term = 0;

float p_yaw_term, i_yaw_term, d_yaw_term = 0;

float pitch_output = 0;
float yaw_output = 0;

unsigned long loopFreq;

Servo pitchESC;
/*Servo yawESC;*/

void setup() {
 pitchESC.attach(6, 1000, 2000);
 pitchESC.write(0);
 delay(4000);
 pitchESC.write(10);
 delay(500);
 pitchESC.write(0);
 
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

 Wire.beginTransmission(0x28); // temp source
 Wire.write(0x40);
 Wire.write(0x00);
 Wire.endTransmission();

 Wire.beginTransmission(0x28); //operation mode
 Wire.write(0x3D);
 Wire.write(0x0C);
 Wire.endTransmission();
 pitchESC.write(0);
 
 delay(100);
 
 loopFreq = micros();
}

void loop() { /* loop frequency = 250hz */ 
 Wire.beginTransmission(0x28);
 Wire.write(0x1C);
 Wire.endTransmission();
 Wire.requestFrom(0x28, 2);
 pitch_lsb = Wire.read(); /*Since msb and lsb are appear in an inverted order in the register map, I can't use a simpler form*/
 pitch_msb = Wire.read();

 Wire.beginTransmission(0x28);
 Wire.write(0x1A);
 Wire.endTransmission();
 Wire.requestFrom(0x28, 2);
 yaw_lsb = Wire.read();
 yaw_msb = Wire.read();

 
 pitchAngle = pitch_msb << 8 | pitch_lsb;
 yawAngle = yaw_msb << 8 | yaw_lsb;

 pitchError = pitchTarget - pitchAngle/16;

 p_pitch_term = p_pitch_const*pitchError;
 i_pitch_term = pitchPrevIterm + i_pitch_const*((pitchError+pitchPrevError)*0.004/2);
 d_pitch_term = d_pitch_const*((pitchError-pitchPrevError)/0.004);

 if(i_pitch_term > 400)
   i_pitch_term = -400;

 else if (i_pitch_term < -400)
   i_pitch_term = -400;
 
 pitch_output = p_pitch_term + i_pitch_term + d_pitch_term; /*if pitch_output > 80, pitch_output = 80*/

 if(pitch_output > 179)
  pitch_output = 179;

 else if (pitch_output < 7)
  pitch_output = 7;

 pitchPrevError = pitchError;
 pitchPrevIterm = i_pitch_term;

 pitchESC.write((int)pitch_output);
 
 while((micros()- loopFreq) < 4000);
 loopFreq = micros();

 
 
 Serial.print("motor output: ");
 Serial.println(pitch_output, DEC);
 Serial.println(""); /*
 Serial.print("Pitch: ");
 Serial.println(pitchAngle/16, DEC);
 Serial.print("Yaw: ");
 Serial.println(yawAngle/16, DEC);
 Serial.println("");*/
}
