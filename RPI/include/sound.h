/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.h
 */

#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <cstdio>

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
		ALuint source_;
		ALuint buffer_;

		int sourcePosX_ = 0;
		int sourcePosY_ = 0;
		int sourcePosZ_ = 0;
};

#endif
