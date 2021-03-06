#pragma config(Sensor, S1,     HTMAG,               sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-magfield-test1.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * hitechnic-magfield.h provides an API for the HiTechnic Magnetic Field Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 27 July 2010
 * version 0.1
 */

#include "drivers/hitechnic-magfield.h"

task main () {

  int magFieldValue = 0;
  int calibrationValue = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "MAGNETIC");
  nxtDisplayCenteredTextLine(3, "Field Sensor");
  nxtDisplayCenteredTextLine(4, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect Sensor");
  nxtDisplayCenteredTextLine(6, "to S1");

  wait1Msec(2000);

  nxtDisplayCenteredTextLine(5, "Press enter");
  nxtDisplayCenteredTextLine(6, "to set bias");

  wait1Msec(2000);
  eraseDisplay();
  while(true) {
    eraseDisplay();
    nxtDisplayTextLine(1, "Resetting");
    nxtDisplayTextLine(2, "bias");
    wait1Msec(500);

    // Start the calibration and display the offset
    calibrationValue = HTMAGstartCal(HTMAG);
    nxtDisplayTextLine(2, "Bias: %4d", calibrationValue);
    PlaySound(soundBlip);
    while(bSoundActive) EndTimeSlice();
    while(nNxtButtonPressed != kNoButton) EndTimeSlice();

    while(nNxtButtonPressed != kEnterButton) {
      eraseDisplay();

      // Read the current calibration offset
      calibrationValue = HTMAGreadCal(HTMAG);

      // Read the current magnetic field strength
      magFieldValue = HTMAGreadVal(HTMAG);

      nxtDisplayTextLine(1, "Reading");
      // Display the current calibration value
      nxtDisplayTextLine(2, "Bias: %4d", calibrationValue);

      nxtDisplayClearTextLine(4);
      // Display the current magnetic field strength
      nxtDisplayTextLine(4, "Mag:   %4d", magFieldValue);
      nxtDisplayTextLine(6, "Press enter");
      nxtDisplayTextLine(7, "to recalibrate");
      wait1Msec(100);
    }
  }
}

/*
 * $Id: hitechnic-magfield-test1.c 127 2012-12-05 19:32:39Z xander $
 */
