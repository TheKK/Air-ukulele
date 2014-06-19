/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: button.cpp
 */

#include "button.h"

Button::Button(int pinNumber):
	pinNumber_(pinNumber)
{
	pinMode(pinNumber_, INPUT);
}

enum ButtonState
Button::State()
{
	int currentValue = digitalRead(pinNumber_);
	
	if ((previousValue_ == 1) && (currentValue == 0)) {
		previousValue_ = 0;
		return BUTTON_PRESSED;
	} else if ((previousValue_ == 0) && (currentValue == 1)) {
		previousValue_ = 1;
		return BUTTON_RELEASED;
	} else
		return BUTTON_NOTHING;
}
