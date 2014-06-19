#ifndef NRF24L01_h
#define NRF24L01_h

#include "API.h"

//---------------------------------------------
#define TX_ADR_WIDTH    5   
// 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  1  
// 20 unsigned chars TX payload
//---------------------------------------------
// You can change the define pin. 
#define CE       8
// CE_BIT:   Digital Input     Chip Enable Activates RX or TX mode

#define CSN      10
// CSN BIT:  Digital Input     SPI Chip Select

#define IRQ     9
// IRQ BIT:  Digital Output    Maskable interrupt pin

#define MISO     12
// MISO BIT: Digital Output  
#define MOSI     11// MOSI BIT: Digital Input   
#define SCK      13

//*********************************************
#endif
