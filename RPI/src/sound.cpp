/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.cpp
 */

#include "sound.h"

Sound::Sound(string filePath)
{
	LoadSoundFile(filePath);
}

Sound::~Sound()
{
	UnloadSoundFile();
}

int
Sound::LoadSoundFile(string filePath)
{
	//Gen buffer
	alGenBuffers(1, &this->buffer);

	//Make a source
	alGenSources(1, &this->source);

	//Load audio file
	this->buffer = alureCreateBufferFromFile(filePath.c_str());

	alSourcei(this->source, AL_BUFFER, this->buffer);

	return 0;
}

int
Sound::UnloadSoundFile()
{
	alDeleteSources(1, &this->source);
	if (alGetError() != AL_NO_ERROR)
		return -1;

	alDeleteBuffers(1, &this->buffer);
	if (alGetError() != AL_NO_ERROR)
		return -1;

	return 0;
}

void
Sound::SetSourcePosition(int x, int y, int z)
{
	this->sourcePosX = x;
	this->sourcePosY = y;
	this->sourcePosZ = z;

	alSource3i(this->source, AL_POSITION, x, y, z);
}

void
Sound::Play()
{
	alSourcePlay(this->source);
}

void
Sound::Stop()
{
	alSourceStop(this->source);
}

void
Sound::Pause()
{
	alSourcePause(this->source);
}
