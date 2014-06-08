/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: chord.cpp
 */

#include "chord.h"

Chord::Chord(string sound1, string sound2, string sound3, string sound4, string sound5)
{
	for (int i = 0; i < NUMBER_OF_STRING; i++)
		stringIsPressed[i] = false;

	LoadAllSound(sound1, sound2, sound3, sound4, sound5);
}

Chord::~Chord()
{
	UnloadAllSound();
}

int
Chord::LoadAllSound(string sound1, string sound2, string sound3, string sound4, string sound5)
{
	sound_[0] = new Sound(sound1);
	sound_[1] = new Sound(sound2);
	sound_[2] = new Sound(sound3);
	sound_[3] = new Sound(sound4);
	sound_[4] = new Sound(sound5);

	return 0;
}

int
Chord::UnloadAllSound()
{
	for (int i = 0; i < NUMBER_OF_STRING; i++) {
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
	assert(position >= 1 && position <= 5);

	switch (position) {
		case 1:
			stringIsPressed[0] = true;
			break;
		case 2:
			stringIsPressed[1] = true;
			break;
		case 3:
			stringIsPressed[2] = true;
			break;
		case 4:
			stringIsPressed[3] = true;
			break;
		case 5:
			stringIsPressed[4] = true;
			break;
	}
}

void
Chord::ReleaseFromString(int position)
{
	assert(position >= 1 && position <= 5);

	switch (position) {
		case 1:
			stringIsPressed[0] = false;
			break;
		case 2:
			stringIsPressed[1] = false;
			break;
		case 3:
			stringIsPressed[2] = false;
			break;
		case 4:
			stringIsPressed[3] = false;
			break;
		case 5:
			stringIsPressed[4] = false;
			break;
	}
}

void
Chord::Pluck()
{
	//Stop playing sound
	sound_[nowPlaying]->Stop();

	for (int i = NUMBER_OF_STRING - 1; i >= 0; i--)
		if (stringIsPressed[i]) {
			sound_[i]->Play();
			nowPlaying = i;
			return;
		}
}
