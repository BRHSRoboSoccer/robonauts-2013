#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     MotorControllers, sensorNone)
#pragma config(Sensor, S2,     KickerTouch,    sensorTouch)
#pragma config(Sensor, S3,     SMUX1,          sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX2,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Sensor Setup:

S1: MotorControllers (TETRIX Motor Controllers)
S2: KickerTouch
S3: SMUX1 (HiTechnic Sensor Multiplexer)
		1 - IRBack (HiTechnic IRSeeker V2)
		2 - IRFront (HiTechnic IRSeeker V2)
		3 - USBack (Lego Ultrasonic Sensor)
		4 - USRight (Lego Ultrasonic Sensor)
S4: SMUX2 (MindSensors Port Splitter)
		1 - Colour (HiTechnic Color Sensor V2)
		2 - HaveBaller (Lego Touch Sensor)
		3	- Compass (HiTechnic Compass Sensor)
*/

#include "common.h"
#include "hitechnic-sensormux.h"
#include "hitechnic-irseeker-v2.h"
#include "hitechnic-compass.h"
#include "hitechnic-colour-v2.h"
#include "hitechnic-sensormux.h"

const tMUXSensor IRBack = msensor_S3_1;
const tMUXSensor IRFront = msensor_S3_2;
const tMUXSensor USBack = msensor_S3_3;
const tMUXSensor USRight = msensor_S3_4;
const tMUXSensor Colour = msensor_S4_1;
const tMUXSensor HaveBaller = msensor_S4_2;
const tMUXSensor Compass = msensor_S4_3;

#define ST  0
#define F   1
#define FR  2
#define R   3
#define BR  4
#define B   5
#define BL  6
#define L   7
#define FL  8
#define CW  9
#define CC  10

#define nbound 20
#define rbound 30
#define lbound 152
#define fbound 213
#define bbound 30

#define power 15
#define turnPower 10

	long currentRed = 0;
  long currentGreen = 0;
  long currentBlue = 0;
	long gRed = 0;
  long gGreen = 0;
  long gBlue = 0;
  long wRed = 0;
  long wGreen = 0;
  long wBlue = 0;
  long bRed = 0;
  long bGreen = 0;
  long bBlue = 0;
  int _target = 0;

							//y	x		(   motorFL,   	motorFR,	  motorBR,	  motorBL)
int const mov[11][4]={{					0,			    0,     	 		0, 	        0},  //ST
                      {		 -power,			power,			power,		 -power},  //F
                      {		 -power,					0,			power,					0},  //FR
                      {		 -power,		 -power,			power,			power},  //R
                      {					0,		 -power,					0,			power},  //BR
                      {			power,		 -power,		 -power,			power},  //B
                      {			power,				  0,		 -power,					0},  //BL
                      {			power,			power,		 -power,		 -power},  //L
                      {					0,			power,					0,		- power},  //FL
                      {-turnPower, -turnPower, -turnPower, -turnPower},  //CW
                      {	turnPower,	turnPower,  turnPower,  turnPower}}; //CC

void move(int dir){
	motor[motorFL]=mov[dir][0];
	motor[motorFR]=mov[dir][1];
	motor[motorBR]=mov[dir][2];
	motor[motorBL]=mov[dir][3];
}

void calibrate(){
	wait10Msec(20);
  while(nNxtButtonPressed != kEnterButton) {
		nxtDisplayCenteredTextLine(0, "Robonauts");
		nxtDisplayCenteredTextLine(1, "Offense");
		nxtDisplayCenteredBigTextLine(3, "Calibrate Compass");
		nxtDisplayTextLine(4, "Abs:   %4d", HTMCreadHeading(Compass));
		nxtDisplayCenteredTextLine(6, "Press Enter");
 	}
 	eraseDisplay();
 	nxtDisplayTextLine(2, "Setting");
  nxtDisplayTextLine(3, "target");
  wait1Msec(500);
  // Set the current heading as the value for the offset to be used as the
  // new zero-point for the relative heading returned by
  // HTMCreadRelativeHeading()
  _target = HTMCsetTarget(Compass);
  PlaySound(soundBlip);
  while(bSoundActive){
  	EndTimeSlice();
  }
  while(nNxtButtonPressed != kEnterButton) {
		nxtDisplayCenteredTextLine(0, "Robonauts");
		nxtDisplayCenteredTextLine(1, "Offense");
		nxtDisplayCenteredBigTextLine(3, "START ROBOT");
		nxtDisplayCenteredTextLine(6, "Press Enter");
 	}
 	eraseDisplay();
}


task main(){
	calibrate();
	while(true){
		int relCompass = HTMCreadRelativeHeading(Compass);
		nxtDisplayTextLine(5, "Rel:   %4d", relCompass);
		if(relCompass < -nbound){
			move(CC);
		}
		else if(relCompass > nbound){
			move(CW);
		}
		else{
			move(ST);
		}
	}
}
