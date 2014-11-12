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
    BUTTON_NOTHING = 0x00,
    BUTTON_PRESSED,
    BUTTON_RELEASED
};

class Button
{
	public:
		Button(int pinNum);
		enum ButtonState State();
	private:
		int pinNum_;
        int prevValue_;
};

#endif
