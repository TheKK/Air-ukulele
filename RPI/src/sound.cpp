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
	alGenBuffers(1, &buffer_);

	//Make a source_
	alGenSources(1, &source_);

	//Load audio file
	buffer_ = alureCreateBufferFromFile(filePath.c_str());
	if (buffer_ == AL_NONE) {
		fprintf(stderr, "AL error: file %s not found\n", filePath.c_str());
		return -1;
	}

	alSourcei(source_, AL_BUFFER, buffer_);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "AL error: %s", alureGetErrorString());
		return -1;
	}

	return 0;
}

int
Sound::UnloadSoundFile()
{
	alDeleteSources(1, &source_);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "AL error: %s", alureGetErrorString());
		return -1;
	}

	alDeleteBuffers(1, &buffer_);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "AL error: %s", alureGetErrorString());
		return -1;
	}

	return 0;
}

void
Sound::SetSourcePosition(int x, int y, int z)
{
	sourcePosX_ = x;
	sourcePosY_ = y;
	sourcePosZ_ = z;

	alSource3i(source_, AL_POSITION, x, y, z);
}

void
Sound::Play()
{
	alSourcePlay(source_);
}

void
Sound::Stop()
{
	alSourceStop(source_);
}

void
Sound::Pause()
{
	alSourcePause(source_);
}
