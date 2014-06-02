/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.cpp
 */

#include "soundEngine.h"

ALCdevice* SoundEngine::device;
ALCcontext* SoundEngine::context;

int SoundEngine::listenerPosX;
int SoundEngine::listenerPosY;
int SoundEngine::listenerPosZ;

int
SoundEngine::Init()
{
	//Init device
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);

	alcMakeContextCurrent(context);

	//Init listener position
	listenerPosX = 0;
	listenerPosY = 0;
	listenerPosZ = 0;
	alListener3i(AL_POSITION, listenerPosX, listenerPosY, listenerPosZ);

	if (CheckError() < 0)
		return -1;
	else
		return 0;
}

void
SoundEngine::Quit()
{
	alcMakeContextCurrent(NULL);

	alcDestroyContext(context);
	context = NULL;

	alcCloseDevice(device);
	device = NULL;
}

int
SoundEngine::CheckError()
{
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "ALURE error: %s\n", alureGetErrorString());
		return -1;
	} else
		return 0;
}
