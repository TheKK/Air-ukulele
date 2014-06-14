/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: spi.h
 */

#ifndef SPI_H
#define SPI_H

#include <iostream>
#include <fstream>
#include <string>

extern "C"
{
#include <fcntl.h>
#include <asm-generic/ioctl.h>
#include <linux/spi/spidev.h>
};

using namespace std;

class SPIDevice
{
	public:
		SPIDevice(string chipSelect, string bus = "0")
		{
			string devPath = "/dev/apidev" + bus + "." + chipSelect;
			fd = open(devPath.c_str(), O_RDWR);

			if (fd < 0)
				cout << "device not found" << endl;
			else
				cout << "device found!" << endl;
		}

		void
		transaction()
		{

		}
	private:
		int fd;
};

#endif
