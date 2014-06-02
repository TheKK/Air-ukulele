/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: test.cpp
 */

#include <iostream>
#include <cstdio>
#include <thread>

extern "C"
{
#include <unistd.h>
}

#include "gpio.h"
#include "sound.h"
#include "soundEngine.h"

using namespace std;

bool appIsRunning = true;

//Sounds
Sound* testSound = NULL;

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	testSound = new Sound("./sound/sound.wav");

	return 0;
}

void
EventHandler(int event)
{
	switch (event) {
		//q, quit
		case 113:
			appIsRunning = false;
			break;
		//z, trigger 1
		case 122:
			testSound->Play();
	}
}

void
Update()
{
}

void
CleanUp()
{
	SoundEngine::Quit();
}

void
gpioStateChecker()
{
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	int event;

	while (appIsRunning) {
		event = getc(stdin);
		printf("%d\n", event);

		EventHandler(event);

		Update();
	}

	CleanUp();

	return 0;
}
