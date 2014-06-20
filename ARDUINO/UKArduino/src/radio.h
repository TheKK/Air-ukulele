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

#include <SPI.h>
#include "API.h"
#include "nRF24L01.h"

//***************************************************
#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  10  // the numbers of unsigned chars TX payload


//***************************************************
void radio_Setup();

void radio_SendData(unsigned char data);

//**************************************************
// Function: init_io();
// Description:
// flash led one time,chip enable(ready to TX or RX Mode),
// Spi disable,Spi clock line init high
//**************************************************
void init_io(void);

/************************************************************************
 **   * Function: SPI_RW();
 *
 * Description:
 * Writes one unsigned char to nRF24L01, and return the unsigned char read
 * from nRF24L01 during write, according to SPI protocol
 ************************************************************************/
unsigned char SPI_RW(unsigned char Byte);


/**************************************************
 * Function: SPI_RW_Reg();
 *
 * Description:
 * Writes value 'value' to register 'reg'
/**************************************************/
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value);

/**************************************************
 * Function: SPI_Read();
 *
 * Description:
 * Read one unsigned char from nRF24L01 register, 'reg'
/**************************************************/
unsigned char SPI_Read(unsigned char reg);

/**************************************************
 * Function: SPI_Read_Buf();
 *
 * Description:
 * Reads 'unsigned chars' #of unsigned chars from register 'reg'
 * Typically used to read RX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);

/**************************************************
 * Function: SPI_Write_Buf();
 *
 * Description:
 * Writes contents of buffer '*pBuf' to nRF24L01
 * Typically used to write TX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);

/**************************************************
 * Function: TX_Mode();
 *
 * Description:
 * This function initializes one nRF24L01 device to
 * TX mode, set TX address, set RX address for auto.ack,
 * fill TX payload, select RF channel, datarate & TX pwr.
 * PWR_UP is set, CRC(2 unsigned chars) is enabled, & PRIM:TX.
 *
 * ToDo: One high pulse(>10us) on CE will now send this
 * packet and expext an acknowledgment from the RX device.
 **************************************************/
void TX_Mode(void);
