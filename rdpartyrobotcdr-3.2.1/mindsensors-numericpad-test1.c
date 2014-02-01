#pragma config(Sensor, S1,     MSNP,                sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-numericpad-test1.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * mindsensors-numericpad.h provides an API for the Mindsensors Numeric Keypad Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 30 October 2010
 * version 0.1
 */

#include "drivers/mindsensors-numericpad.h"

task main () {

  int keys = 0;
  unsigned byte key[] = {0};
  int number = 0;
  string output;

  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "NumPad");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);

  eraseDisplay();
  nxtDisplayCenteredTextLine(0, "Mindsensors NP");
  nxtDisplayTextLine(1, "-------------------");
  nxtDisplayTextLine(5, "-------------------");
  nxtDisplayTextLine(7, "X: no key");
  while (true) {
    // Which key is being pressed now?
    if (!MSNPscanKeys(MSNP, keys, key[0], number))
      StopAllTasks();

    // "convert" to string so we can print it
    output = key;

    nxtDisplayTextLine(3, "Numpad Key: %s", output);
    nxtDisplayTextLine(4, "Numpad Num: %d", number);

    wait1Msec(100);
  }
}

/*
 * $Id: mindsensors-numericpad-test1.c 127 2012-12-05 19:32:39Z xander $
 */
