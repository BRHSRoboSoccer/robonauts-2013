#pragma config(Sensor, S4,     NXT2WIFI,       sensorHighSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: benedettelli-nxt2wifi-setup.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * benedettelli-nxt2wifi.h provides an API for Daniele's NXT2WiFi Sensor. This program allows
 * to quickly retrieve the IP address and MAC so you can activate the sensor.  It will do the following:
 * - Delete the custom profile
 * - Reset the device
 * - Setup the default profile, which is an AdHoc network called NXT2WIFI
 *
 * When it's done setting up the AdHoc network, it will display the IP and MAC address. Use the MAC
 * address to retrieve an activation key from http://dev.openpicus.com/Firmware/NXT2WIFI
 *
 * Connect to the AdHoc network (NXT2WIFI) and point your browser to http://<IP on NXT>/activate.htm to activate
 * it using the code you got from the activation page.
 *
 * You're now good to go!
 *
 * Use benedetelli-nxt2wifi-config.c to create a custom profile
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Daniele Benedettelli for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.00 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 22 July 2012
 * version 0.1
 */
#define __RS485_DEBUG__
#include "drivers/common.h"
#include "drivers/benedettelli-nxt2wifi.h"

//string returnMsg;
string IPaddress;
string MACaddress;

task main ()
{
  nxtDisplayTextLine(0, "Stat: disconnected");
  nxtDisplayTextLine(2, "-------------------");

  // port to use for the socket
  string dataString;

  // get our bluetooth name
  getFriendlyName(dataString);

  // initialise the port, etc
  RS485initLib();
  N2WchillOut();

  N2WsetDebug(true);
  N2WchillOut();

  // Disconnect if already connected
  N2WDisconnect();
  wait1Msec(100);

  // Delete the custom profile and reset the device
  N2WDelete();
  wait1Msec(100);
  N2WReset();
  nxtDisplayTextLine(0, "Stat: Resetting");
  wait1Msec(5000);

  // Connect to the default profile (AdHoc)
  nxtDisplayTextLine(0, "Stat: Connecting");
  N2WConnect(false);

  while (!N2WConnected())
    wait1Msec(500);

  wait1Msec(2000);
  N2WgetIP(IPaddress);
  nxtDisplayTextLine(4, IPaddress);
  wait1Msec(100);
  N2WgetMAC(MACaddress);
  nxtDisplayTextLine(5, MACaddress);
  nxtDisplayTextLine(0, "Stat: Connected");
  PlaySound(soundBeepBeep);

  while(true) EndTimeSlice();

}
