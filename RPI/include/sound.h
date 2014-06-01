/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: sound.h
 */

#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>

extern "C"
{
#include <AL/al.h>
#include <AL/alut.h>
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

		//Sound control
		void Play();
		void Stop();
		void Pause();

	private:
		ALuint source;

		ALuint buffer;

		ALint state;

		//ALenum format;
		//ALsizei size;
		//ALvoid* data;
		//ALsizei freq;
		//ALboolean loop;
};

#endif
