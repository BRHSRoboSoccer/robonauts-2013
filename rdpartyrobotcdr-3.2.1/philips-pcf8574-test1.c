#pragma config(Sensor, S2,     PCF8574,             sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: philips-pcf8574-test1.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * philips-pcf8574.h provides an API for the Philips PCF8574 IO MUX. This program
 * demonstrates how to use that API to control the motors attached to the MUX.
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
 * 30 March 2010
 * version 0.1
 */

#include "drivers/philips-pcf8574.h"

task main () {
  while (true) {
	  for (int i = 0; i < 8; i++) {
	    int foo = 1 << i;
	    foo = ~foo;
	    PCF8574sendBytes(PCF8574, foo);
	    wait1Msec(50);
	  }
	  for (int i = 7; i > -1; i--) {
	    int foo = 1 << i;
	    foo = ~foo;
	    PCF8574sendBytes(PCF8574, foo);
	    wait1Msec(50);
	  }
  }
}

 /*
 * $Id: philips-pcf8574-test1.c 127 2012-12-05 19:32:39Z xander $
 */
