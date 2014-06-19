/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: button.h
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

extern "C"
{
#include <wiringPi.h>
};

using namespace std;

enum ButtonState
{
	BUTTON_NOTHING = 0x01,
	BUTTON_PRESSED,
	BUTTON_RELEASED
};

class Button
{
	public:
		Button(int pinNumber);

		enum ButtonState State();
	private:
		int pinNumber_;
		/*
		 * Because we use pull up resistor,
		 * when the button is setup its default value is 1.
		 * When this button is pressed, its value will turn 0.
		 * When this button is released, its value will turn 1 again.
		 */
		int previousValue_ = 1;
};

#endif
