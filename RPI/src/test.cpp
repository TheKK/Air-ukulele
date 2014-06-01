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

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	return 0;
}

void
EventHandler()
{
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
	fprintf(stdout, "From another thread\n");
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	Sound testSound("./sound/sound.wav");
	testSound.Play();

	//while (appIsRunning) {
		//EventHandler();
		//Update();
	//}

	sleep(2);

	CleanUp();

	return 0;
}
