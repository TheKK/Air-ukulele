/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spi.h
 */

/*
 * This class is a port from Arduino version, EF_nRF24L01_TX.c, made by ElecFraks.
 * Please checkout his/her site http://www.elecfreaks.com
 */

#ifndef NRF24_H
#define NRF24_H

#include <iostream>

extern "C"
{
#include <wiringPi.h>
#include <wiringPiSPI.h>
};

#include "NRF24L01.h"

#define TX_ADR_WIDTH	5
#define TX_PLOAD_WIDTH	10

using namespace std;

class NRF24
{
	public:
		NRF24(int SPIChannel, int rfChannel, int speed, int cePin, int csnPin);
		~NRF24();

		unsigned char ReceiveData();
	private:
		unsigned char TX_ADDRESS[TX_ADR_WIDTH] =
		{
			0x34, 0x43, 0x10, 0x10, 0x01
		};

		unsigned char rx_buf[TX_PLOAD_WIDTH] = {0};

		int cePin;
		int csnPin;

		unsigned char SPI_RW(unsigned char byte);
		unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value);
		unsigned char SPI_Read(unsigned char reg);
		unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);
		unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);
		void RX_Mode(int channel);
		void IO_Init();

};

#endif
