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
	BUTTON_ALL_RELEASE,
	BUTTON1_PRESSED,
	BUTTON2_PRESSED,
	BUTTON3_PRESSED,
	BUTTON4_PRESSED,
	BUTTON5_PRESSED
};

class Button
{
	public:
		Button(int pin1, int pin2, int pin3);

		enum ButtonState State();
	private:
		int pinNumber_[3];
		enum ButtonState previousState = BUTTON_NOTHING;
		
};

#endif
