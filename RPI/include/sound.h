/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.h
 */

#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <cstdio>
#include <cassert>

extern "C"
{
#include <AL/al.h>
#include <AL/alure.h>
}

using namespace std;

class Sound
{
	public:
		Sound(string filePath);
		~Sound();

		//File operations
		int LoadSoundFile(string filePath);
		int UnloadSoundFile();

		void SetSourcePosition(int x, int y, int z);

		//Sound control
		void Play();
		void Stop();
		void Pause();

	private:
		ALuint source;
		ALuint buffer;

		int sourcePosX = 0;
		int sourcePosY = 0;
		int sourcePosZ = 0;
};

#endif
