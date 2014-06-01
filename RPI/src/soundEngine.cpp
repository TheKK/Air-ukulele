/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.cpp
 */

#include "soundEngine.h"

int
SoundEngine::Init()
{
	alutInit(NULL, NULL);

	if (CheckError() < 0)
		return -1;
	else
		return 0;
}

int
SoundEngine::Quit()
{
	alutExit();

	if (CheckError() < 0)
		return -1;
	else
		return 0;
}

int
SoundEngine::CheckError()
{
	if (alutGetError() != ALUT_ERROR_NO_ERROR) {
		fprintf(stderr, "ALUT error: %s\n", alutGetErrorString(alutGetError()));
		return -1;
	}
	else
		return 0;
}
