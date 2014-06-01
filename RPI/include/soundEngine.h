/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: soundEngine.h
 */

#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <iostream>
#include <cstdio>

extern "C"
{
#include <AL/al.h>
#include <AL/alut.h>
}

using namespace std;

class SoundEngine
{
	public:
		static int Init();
		static int Quit();

	private:
		static int CheckError();
};

#endif
