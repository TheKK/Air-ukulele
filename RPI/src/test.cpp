/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: test.cpp
 */

#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <thread>

extern "C"
{
#include <wiringPi.h>
#include <unistd.h>
}

#include "button.h"

bool appIsRunning = true;
Button* button11;

using namespace std;

int
Init()
{
	return 0;
}


int
main(int argc, char* argv[])
{
	wiringPiSetup();

	while (appIsRunning) {
		enum ButtonState state = button11->State();
		if (state == BUTTON_PRESSED)
			printf("PRESSED\n");
		else if (state == BUTTON_RELEASED)
			printf("RELEASED\n");
	}

	delete button11;
	button11 = NULL;

	return 0;
}
