/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gpio.cpp
 */

#include "gpio.h"

GPIO::GPIO(string pinNumber, string direction):
	pinNumber_(pinNumber),
	direction_(direction)
{
	ExportPin();
	SetPinDirection(direction_);
}

GPIO::~GPIO()
{
}

int
GPIO::ExportPin()
{
	string command = "gpio-admin export " + pinNumber_;

	if (system(command.c_str()) > 0) {
		fprintf(stderr, "Can not execute gpio-admin, please check if you install it\n");
		return -1;
	} else
		return 0;
}

int
GPIO::UnexportPin()
{
	string command = "gpio-admin unexport " + pinNumber_;

	if (system(command.c_str()) > 0) {
		fprintf(stderr, "Can not execute gpio-admin, please check if you install it\n");
		return -1;
	} else
		return 0;
}

int
GPIO::SetPinDirection(string direction)
{
	//Make sure input vaule is valid
	assert(direction == "in" || direction == "out");
	direction_ = direction;

	string filePath = "/sys/class/gpio/gpio" + pinNumber_ + "/direction";

	ofstream setPinDirection(filePath.c_str());
	if (setPinDirection < 0) {
		fprintf(stderr, "GPIO error: Can not set direction of GPIO%s\n", pinNumber_.c_str());
		return -1;
	}

	setPinDirection << direction_;
	setPinDirection.close();

	return 0;
}

int
GPIO::SetPinValue(string value)
{
	string filePath = "/sys/class/gpio/gpio" + pinNumber_ + "/value";

	ofstream setPinValue(filePath.c_str());
	if (setPinValue < 0) {
		fprintf(stderr, "GPIO error: Can not set value of GPIO%s\n", pinNumber_.c_str());
		return -1;
	}

	setPinValue << value;
	setPinValue.close();

	return 0;
}

int
GPIO::GetPinValue(string& value)
{
	string filePath = "/sys/class/gpio/gpio" + pinNumber_ + "/value";

	ifstream getPinValue(filePath.c_str());
	if (getPinValue < 0) {
		fprintf(stderr, "GPIO error: Can not set value of GPIO%s\n", pinNumber_.c_str());
		return -1;
	}

	getPinValue >> value;
	getPinValue.close();

	return 0;
}

string
GPIO::GetPinNumber()
{
	return pinNumber_;
}
