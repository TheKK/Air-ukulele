/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: test.cpp
 */

#include <iostream>
#include <cstdio>

extern "C"
{
#include <AL/al.h>
#include <AL/alut.h>
#include <unistd.h>
}

#include "gpio.h"
#include "sound.h"

using namespace std;

int
main(int argc, char* argv[])
{
	alutInit(NULL, NULL);

	Sound testSound("./sound/sound.wav");
	testSound.Play();

	sleep(2);

	alutExit();

	return 0;
}
