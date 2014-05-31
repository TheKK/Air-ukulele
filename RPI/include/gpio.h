/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gpio.h
 */

#ifndef GPIO_H
#define GPIO_H

#include <iostream>
#include <ofstream>
#include <string>
#include <cassert>

class GPIO
{
	public:
		GPIO(int pinNumber): pinNumber(pinNumber);
		~GPIO();

		int ExportPin(int pinNumber);
		int UnexportPin(int pinNumber);
		int SetPinDirection(string direction);
		int SetPinValue(string value);
		int GetPinValue();

	private:
		unsigned int pinNumber;
};

#endif
