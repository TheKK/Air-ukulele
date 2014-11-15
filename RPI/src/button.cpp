/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: button.cpp
 */

#include "button.h"

Button::Button(int pinNum)
{
    pinNum_ = pinNum;
}

enum ButtonState
Button::State()
{
	int currentValue;

	currentValue = digitalRead(pinNum_);

    if (prevValue_ == 0 && currentValue == 1)
        return BUTTON_PRESSED;

    if (prevValue_ == 1 && currentValue == 0)
        return BUTTON_RELEASED;

    return BUTTON_NOTHING;
}
