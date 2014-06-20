/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: chord.h
 */

#ifndef CHORD_H
#define CHORD_H

#include <iostream>
#include <string>
#include <cassert>

#include "sound.h"

#define NUMBER_OF_POSITION	5

using namespace std;


class Chord
{
	public:
		Chord(string sound1, string sound2, string sound3, string sound4, string sound5, string sound6);
		~Chord();

		int LoadAllSound(string sound1, string sound2, string sound3, string sound4, string sound5, string sound6);
		int UnloadAllSound();

		int LoadASound(int which, string sound);
		int UnloadASound(int which);

		void PressOnString(int position);
		void ReleaseFromString();

		void Pluck();
	private:
		Sound* sound_[NUMBER_OF_POSITION + 1];

		int nowPlaying_ = 0;
		int nowPressing_ = 0;

};

#endif
