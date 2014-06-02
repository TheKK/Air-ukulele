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
#include <AL/alure.h>
}

using namespace std;

class SoundEngine
{
	public:
		static int Init();
		static void Quit();

		static int SetListenerPos(int x, int y, int z );

	private:
		static int CheckError();

		static ALCdevice* device;
		static ALCcontext* context;

		//Listener position
		static int listenerPosX;
		static int listenerPosY;
		static int listenerPosZ;
};

#endif
