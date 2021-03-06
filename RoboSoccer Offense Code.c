#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     MotorControllers, sensorNone)
#pragma config(Sensor, S2,     HaveBaller,     sensorTouch)
#pragma config(Sensor, S3,     SMUX1,          sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX2,          sensorI2CCustom)
#pragma config(Motor,  motorB,          Kicker,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Dribbler,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFL,       tmotorTetrix, openLoop)
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
		3 - Compass (HiTechnic Compass Sensor)
*/

#include "common.h"
#include "hitechnic-sensormux.h"
#include "hitechnic-irseeker-v2.h"
#include "hitechnic-compass.h"
#include "hitechnic-colour-v2.h"
#include "lego-touch.h"
#include "lego-ultrasound.h"

const tMUXSensor IRFront = msensor_S3_1;
const tMUXSensor USBack = msensor_S3_3;
const tMUXSensor Colour = msensor_S3_4;
const tMUXSensor IRBack = msensor_S4_1;
const tMUXSensor USLeft = msensor_S4_2;
const tMUXSensor USRight = msensor_S4_3;
const tMUXSensor Compass = msensor_S4_4;

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

#define nbound 30
#define rbound 25
#define lbound 25
#define fbound 200
#define bbound 30
#define whiteThreshold 200

#define power 30
#define turnPower 15

  long currentRed = 0;
  long currentGreen = 0;
  long currentBlue = 0;
  //long gRed = 0;
  //long gGreen = 0;
  //long gBlue = 0;
  int _target = 0;
  int length;
	int rightWidth;
	int leftWidth;
	bool haveBall;
	int frontIRValue;
	int backIRValue;
	int currentRelCompass;
	bool isWhite;


										//(   motorFL,   	motorFR,	  motorBR,	  motorBL)
int const mov[11][4]={{				0,			    0,     	 		0, 	        0},  //ST
                      {		 -1.4,		 			1,					1,		 	-1.4},  //F
                      {		 -1.4,					0,					1,					0},  //FR
                      {		 -1.4,		 			-1,					1,			1.4},  //R
                      {				0,		 			-1,					0,			1.4},  //BR
                      {			1.4,		 			-1,					-1,			1.4},  //B
                      {			1.4,				  0,					-1,				0},  //BL
                      {			1.4,					1,					-1,		 -1.4},  //L
                      {				0,					1,					0,		-1.4},  //FL
                      {		 -1.4,			 -1, 				 -1, -1.4}, //CW
                      {			1.4,				1,	  			1,  1.4}}; //CC

void move(int dir){
	motor[motorFL]= (int)( mov[dir][0] * power/ 1.3);
	motor[motorFR]= (int)(mov[dir][1] * power);
	motor[motorBR]= (int)(mov[dir][2] * power);
	motor[motorBL]= (int)(mov[dir][3] * power / 1.3);
	wait1Msec(50);
	motor[motorFL]= (int)( mov[dir][0] * power);
	motor[motorFR]= (int)(mov[dir][1] * power);
	motor[motorBR]= (int)(mov[dir][2] * power);
	motor[motorBL]= (int)(mov[dir][3] * power);
}

void move(int dir, int motorPow){
	motor[motorFL]= (int)( mov[dir][0] * motorPow / 1.3);
	motor[motorFR]= (int)(mov[dir][1] * motorPow);
	motor[motorBR]= (int)(mov[dir][2] * motorPow);
	motor[motorBL]= (int)(mov[dir][3] * motorPow / 1.3);
	wait1Msec(50);
	motor[motorFL]= (int)( mov[dir][0] * motorPow);
	motor[motorFR]= (int)(mov[dir][1] * motorPow);
	motor[motorBR]= (int)(mov[dir][2] * motorPow);
	motor[motorBL]= (int)(mov[dir][3] * motorPow);
}

void calibrate(){
	eraseDisplay();
	//while(nNxtButtonPressed != kEnterButton) {
	//	nxtDisplayCenteredTextLine(0, "Robonauts");
	//	nxtDisplayCenteredTextLine(1, "Defense");
	//	nxtDisplayCenteredTextLine(3, "Calibrate Green");
	//	nxtDisplayCenteredTextLine(6, "Press Enter");
 //	}
 //	eraseDisplay();
 // HTCS2readRGB(Colour, gRed, gGreen, gBlue);
 // wait10Msec(20);
  //while(nNxtButtonPressed != kEnterButton) {
		//nxtDisplayCenteredTextLine(0, "Robonauts");
		//nxtDisplayCenteredTextLine(1, "Defense");
		//nxtDisplayCenteredBigTextLine(3, "Calibrate Black");
		//nxtDisplayCenteredTextLine(6, "Press Enter");
  //	eraseDisplay();
 	//}
 	//HTCS2readRGB(Colour, bRed, bGreen, bBlue);
  //wait10Msec(20);
  //while(nNxtButtonPressed != kEnterButton) {
		//nxtDisplayCenteredTextLine(0, "Robonauts");
		//nxtDisplayCenteredTextLine(1, "Defense");
		//nxtDisplayCenteredBigTextLine(3, "Calibrate White");
		//nxtDisplayCenteredTextLine(6, "Press Enter");
  //	eraseDisplay();
 	//}
 	//HTCS2readRGB(Colour, wRed, wGreen, wBlue);
  //wait10Msec(20);
  while(nNxtButtonPressed != kEnterButton) {
		nxtDisplayCenteredTextLine(0, "Robonauts");
		nxtDisplayCenteredTextLine(1, "Offense");
		nxtDisplayCenteredTextLine(3, "Calibrate Compass");
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
	motor[Dribbler] = 100;
	while(true){
		length = USreadDist(USBack);
	  rightWidth = USreadDist(USRight);
	  leftWidth = USreadDist(USLeft);
	  haveBall = TSreadState(HaveBaller);
	  frontIRValue = HTIRS2readACDir(IRFront);
	  backIRValue = HTIRS2readACDir(IRBack);
	  currentRelCompass = HTMCreadRelativeHeading(Compass);
	  HTCS2readRGB(Colour, currentRed, currentGreen, currentBlue);
	  isWhite = (currentRed > whiteThreshold && currentGreen > whiteThreshold && currentBlue > whiteThreshold);

	  nxtDisplayTextLine(2, "Com:   %4d", currentRelCompass);
		nxtDisplayTextLine(3, "IR:   %4d", frontIRValue);
		nxtDisplayTextLine(4, "Len:   %4d", length);
		nxtDisplayTextLine(5, "RWid:   %4d", rightWidth);
		nxtDisplayTextLine(6, "LWid:   %4d", leftWidth);
		if(isWhite){
			nxtDisplayTextLine(7, "White:   Yes");
		}
		else{
			nxtDisplayTextLine(7, "White:   No");
		}
		nxtDisplayTextLine(8, "Ball:   %4d", haveBall);


	  if(currentRelCompass < 0 - nbound){
	  	move(CW, turnPower);
	  }
	  else if(currentRelCompass > 0 + nbound){
	  	move(CC, turnPower);
	  }

	  else{
	  	if(isWhite){
	  		if(rightWidth <= rbound){
	  			move(L);
	  		}
	  		else if(leftWidth <= lbound){
	  			move(R);
	  		}
	  	}
	  	else{
	  		if(!haveBall){
	  			if(rightWidth < rbound){
	  				if(length < 10){
	  					move(F);
	  				}
	  				else{
		  				move(L);
		  			}
	  			}
	  			else if(leftWidth < lbound){
	  				if(length < 10){
	  					move(ST);
	  				}
	  				else{
		  				move(R);
		  			}
		  		}
	  			else{
	          if (length > fbound && length != 255){
	            move(B);
	          }

	          else if (length < bbound){
	            move(F);
	          }
	          else{
	          	if(frontIRValue != 2\3){
				        switch(frontIRValue){
				        	case 0:
				        		move(B);
				        		break;
									case 1:
										move(B);
										break;
									case 2:
										move(BL);
										break;
									case 3:
										move(L);
										break;
									case 4:
										move(FL);
										break;
									case 5:
										move(F);
										break;
									case 6:
										move(FR);
										break;
									case 7:
										move(R);
										break;
									case 8:
										move(BR);
										break;
									case 9:
										move(B);
										break;
								}
							}
							else{
								switch(backIRValue){
									case 0:
										move(ST);
										break;
									case 1:
										move(B);
										break;
									case 2:
										move(B);
										break;
									case 3:
										move(B);
										break;
									case 4:
										move(B);
										break;
									case 5:
										move(B);
										break;
									case 6:
										move(B);
										break;
									case 7:
										move(B);
										break;
									case 8:
										move(B);
										break;
									case 9:
										move(B);
										break;
								}
							}
						}
					}
				}
	  		else{
	  			if(rightWidth < 30){
						move(FL);
					}
					else if(leftWidth < 30){
						move(FR);
					}
					else{
						move(F);
					}
			  }
			}
			wait1Msec(50);
		}
	}
}
