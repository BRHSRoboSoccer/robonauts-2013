#pragma config(Sensor, S1,     DIMC,           sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: dexterind-compass-test1.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * dexterind-compass.h provides an API for the Dexter Industries dCompass Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Dexter Industries for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 07 August 2011
 * version 0.1
 */

#include "drivers/dexterind-compass.h"

task main(){

  int x_val, y_val, z_val;      // Compass axes values
  float heading;

  nxtDisplayCenteredTextLine(0, "Dexter Ind.");
  nxtDisplayCenteredBigTextLine(1, "dCompass");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

  // Fire up the compass and initialize it. Only needs to be done once.
  if (!DIMCinit(DIMC))
    PlaySound(soundException);

  wait1Msec(100);
  while (true){

		// Read the Compass
    DIMCreadAxes(DIMC, x_val, y_val, z_val);
    heading = DIMCreadHeading(DIMC);

    nxtDisplayCenteredBigTextLine(2, "%3.2f", heading);
		nxtDisplayTextLine(5, "%d", x_val);
		nxtDisplayTextLine(6, "%d", y_val);
		nxtDisplayTextLine(7, "%d", z_val);
		wait1Msec(50);
  }
}

/*
 * $Id: dexterind-compass-test1.c 127 2012-12-05 19:32:39Z xander $
 */
