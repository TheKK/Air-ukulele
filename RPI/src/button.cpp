/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: button.cpp
 */

#include "button.h"

Button::Button(int pin1, int pin2, int pin3)
{
	pinNumber_[0] = pin1;
	pinNumber_[1] = pin2;
	pinNumber_[2] = pin3;

	pinMode(pinNumber_[0], INPUT);
	pinMode(pinNumber_[1], INPUT);
	pinMode(pinNumber_[2], INPUT);
}

enum ButtonState
Button::State()
{
	int currentValue[3];

	currentValue[0] = digitalRead(pinNumber_[0]);
	currentValue[1] = digitalRead(pinNumber_[1]);
	currentValue[2] = digitalRead(pinNumber_[2]);
	
	if (
			currentValue[0] == 0 &&
			currentValue[1] == 0 &&
			currentValue[2] == 0 &&
			previousState != BUTTON_ALL_RELEASE
	   ) {
		previousState == BUTTON_ALL_RELEASE;
		return BUTTON_ALL_RELEASE;
	} else if (
			currentValue[0] == 1 &&
			currentValue[1] == 0 &&
			currentValue[2] == 0 &&
			previousState != BUTTON1_PRESSED
	   ) {
	}

	if (
			currentValue[0] == 0 &&
			currentValue[1] == 1 &&
			currentValue[2] == 0 &&
			previousState != BUTTON2_PRESSED
	   ) {
	}

	if (
			currentValue[0] == 1 &&
			currentValue[1] == 1 &&
			currentValue[2] == 0 &&
			previousState != BUTTON3_PRESSED
	   ) {
	}

	if (
			currentValue[0] == 0 &&
			currentValue[1] == 0 &&
			currentValue[2] == 1 &&
			previousState != BUTTON4_PRESSED
	   ) {
	}

	if (
			currentValue[0] == 1 &&
			currentValue[1] == 0 &&
			currentValue[2] == 1 &&
			previousState != BUTTON5_PRESSED
	   ) {
	}
}
