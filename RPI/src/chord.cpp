/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: chord.cpp
 */

#include "chord.h"

Chord::Chord(string sound1, string sound2, string sound3, string sound4, string sound5, string sound6)
{
	LoadAllSound(sound1, sound2, sound3, sound4, sound5, sound6);
}

Chord::~Chord()
{
	UnloadAllSound();
}

int
Chord::LoadAllSound(string sound1, string sound2, string sound3, string sound4, string sound5, string sound6)
{
	sound_[0] = new Sound(sound1);
	sound_[1] = new Sound(sound2);
	sound_[2] = new Sound(sound3);
	sound_[3] = new Sound(sound4);
	sound_[4] = new Sound(sound5);
	sound_[5] = new Sound(sound6);

	return 0;
}

int
Chord::UnloadAllSound()
{
	for (int i = 0; i < NUMBER_OF_POSITION; i++) {
		delete sound_[i];
		sound_[i] = NULL;
	}

	return 0;
}

int
Chord::LoadASound(int which, string sound)
{
	sound_[which] = new Sound(sound);

	return 0;
}

int
Chord::UnloadASound(int which)
{
	delete sound_[which];
	sound_[which] = NULL;

	return 0;
}

void
Chord::PressOnString(int position)
{
	assert(position >= 1 && position <= NUMBER_OF_POSITION);

	nowPressing_ = position;
}

void
Chord::ReleaseFromString()
{
	nowPressing_ = 0;
}

void
Chord::Pluck()
{
	sound_[nowPlaying_]->Stop();
	sound_[nowPressing_]->Play();

	nowPlaying_ = nowPressing_;
}
