/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spi.h
 */

/*
 * This class is a port from Arduino version, EF_nRF24L01_TX.c, made by ElecFraks.
 * Please checkout his/her site http://www.elecfreaks.com
 */

#include "spi.h"

NRF24::NRF24(int SPIChannel, int rfChannel, int speed, int cePin, int csnPin):
	cePin(cePin),
	csnPin(csnPin)
{
	pinMode(cePin, OUTPUT);
	pinMode(csnPin, OUTPUT);

	if (wiringPiSPISetup(SPIChannel, speed) < 0) {
		printf("Error while initialize spi device\n");
		exit(1);
	}

	delay(50);

	IO_Init();

	RX_Mode(rfChannel);
}

NRF24::~NRF24()
{
}

unsigned char
NRF24::ReceiveData()
{
	unsigned char status = SPI_Read(STATUS);
	unsigned char toReturn;

	if (status & RX_DR) {
		SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);
		SPI_RW_Reg(FLUSH_RX, 0);

		toReturn = rx_buf[0];
	} else
		toReturn = 0;

	SPI_RW_Reg(WRITE_REG + STATUS, status);

	return toReturn;
}

unsigned char
NRF24::SPI_RW(unsigned char byte)
{
	unsigned char tmp;
	tmp = byte;

	if (wiringPiSPIDataRW(0, &tmp, sizeof(unsigned char)) < 0) {
		printf("Error while write/read spi data\n");
		exit(1);
	}

	return tmp;
}

unsigned char
NRF24::SPI_RW_Reg(unsigned char reg, unsigned char value)
{
	unsigned char status;

	digitalWrite(csnPin, LOW);
	{
		SPI_RW(reg);
		status = SPI_RW(value);
	}
	digitalWrite(csnPin, HIGH);

	return status;
}

unsigned char
NRF24::SPI_Read(unsigned char reg)
{
	unsigned char reg_val;

	digitalWrite(csnPin, LOW);
	{
		SPI_RW(reg);
		reg_val = SPI_RW(0);
	}
	digitalWrite(csnPin, HIGH);

	return reg_val;
}

unsigned char
NRF24::SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
	unsigned char status;

	digitalWrite(csnPin, LOW);
	{
		status = SPI_RW(reg);

		for (unsigned char i = 0; i < bytes; i++)
			pBuf[i] = SPI_RW(0);
	}
	digitalWrite(csnPin, HIGH);

	return status;
}

unsigned char
NRF24::SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
	unsigned char status;

	digitalWrite(csnPin, LOW);
	{
		status = SPI_RW(reg);

		for (unsigned char i = 0; i < bytes; i++)
			SPI_RW(*pBuf++);
	}
	digitalWrite(csnPin, HIGH);

	return status;
}

void
NRF24::RX_Mode(int channel)
{
	digitalWrite(cePin, LOW);
	{
		SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
		SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);
		SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);
		SPI_RW_Reg(WRITE_REG + RF_CH, channel);
		SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
		SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);
	}
	digitalWrite(cePin, HIGH);
}

void
NRF24::IO_Init()
{
	digitalWrite(cePin, LOW);
	digitalWrite(csnPin, HIGH);
}
