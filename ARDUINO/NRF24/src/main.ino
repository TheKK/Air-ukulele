 /*********************************************************************
 **  Device:  nRF24L01+                                              **
 **  File:   EF_nRF24L01_TX.c                                        **
 **                                                                  **
 **                                                                  **
 **  Copyright (C) 2011 ElecFraks.                                   **
 **  This example code is in the public domain.                      **
 **                                                                  **
 **  Description:                                                    **
 **  This file is a sample code for your reference.                  **
 **  It's the v1.0 nRF24L01+ Hardware SPI by arduino                 **
 **  Created by ElecFreaks. Robi.W,11 June 2011                      **
 **                                                                  **
 **  http://www.elecfreaks.com                                       **
 **                                                                  **
 **   SPI-compatible                                                 **
 **   CS - to digital pin 8                                          **
 **   CSN - to digital pin 9  (SS pin)                               **
 **   MOSI - to digital pin 11 (MOSI pin)                            **
 **   MISO - to digital pin 12 (MISO pin)                            **
 **   CLK - to digital pin 13 (SCK pin)                              **
 *********************************************************************/

#include "radio.h"
//***************************************************

void setup()
{
	Serial.begin(9600);
	radio_Setup();
}

void loop()
{
	for (;;)
		radio_SendData('c');
}
