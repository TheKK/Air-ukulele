/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: test.cpp
 */

#include <iostream>

extern "C"
{
#include <unistd.h>
}

#include "gpio.h"
#include "sound.h"
#include "soundEngine.h"

using namespace std;

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	return 0;
}

void
CleanUp()
{
	SoundEngine::Quit();
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	Sound testSound("./sound/sound.wav");
	testSound.Play();

	sleep(2);

	CleanUp();

	return 0;
}
