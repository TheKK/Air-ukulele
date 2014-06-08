/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.cpp
 */

#include "soundEngine.h"

ALCdevice* SoundEngine::device_;
ALCcontext* SoundEngine::context_;

int SoundEngine::listenerPosX_;
int SoundEngine::listenerPosY_;
int SoundEngine::listenerPosZ_;

int
SoundEngine::Init()
{
	//Init device
	device_ = alcOpenDevice(NULL);
	context_ = alcCreateContext(device_, NULL);

	alcMakeContextCurrent(context_);

	//Init listener position
	listenerPosX_ = 0;
	listenerPosY_ = 0;
	listenerPosZ_ = 0;
	alListener3i(AL_POSITION, listenerPosX_, listenerPosY_, listenerPosZ_);

	if (CheckError() < 0)
		return -1;
	else
		return 0;
}

void
SoundEngine::Quit()
{
	alcMakeContextCurrent(NULL);

	alcDestroyContext(context_);
	context_ = NULL;

	alcCloseDevice(device_);
	device_ = NULL;
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
