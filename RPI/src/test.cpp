/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: test.cpp
 */

#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <thread>

extern "C"
{
#include <unistd.h>
#include <curses.h>
}

#include "gpio.h"
#include "sound.h"
#include "soundEngine.h"

using namespace std;

bool appIsRunning = true;
queue<int> keyEventQueue;

//Sounds
Sound* sound1 = NULL;
Sound* sound2 = NULL;
Sound* sound3 = NULL;
Sound* sound4 = NULL;
Sound* sound5 = NULL;
Sound* sound6 = NULL;

int
Init()
{
	//My class
	if (SoundEngine::Init() < 0)
		return 1;

	//Load sound
	sound1 = new Sound("./sound/star1.wav");
	sound2 = new Sound("./sound/star2.wav");
	sound3 = new Sound("./sound/star3.wav");
	sound4 = new Sound("./sound/star4.wav");
	sound5 = new Sound("./sound/star5.wav");
	sound6 = new Sound("./sound/star6.wav");

	//Ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);

	printw("Let's rock!\n");
	printw("Use 's''d''f''j''k' to make some noise.\n");

	return 0;
}

void
EventHandler(int event)
{
	switch (event) {
		case 'q':
			appIsRunning = false;
			break;
		case 's':
			sound1->Play();
			break;
		case 'd':
			sound2->Play();
			break;
		case 'f':
			sound3->Play();
			break;
		case 'j':
			sound4->Play();
			break;
		case 'k':
			sound5->Play();
			break;
		case 'l':
			sound6->Play();
			break;
		case ' ':
			sound1->Play();
			sound2->Play();
			sound3->Play();
			sound4->Play();
			sound5->Play();
			sound6->Play();
			break;
	}
}

void
Update()
{
}

void
CleanUp()
{
	SoundEngine::Quit();

	delete sound1;
	sound1 = NULL;

	delete sound2;
	sound2 = NULL;

	delete sound3;
	sound3 = NULL;

	delete sound4;
	sound4 = NULL;

	delete sound5;
	sound5 = NULL;

	delete sound6;
	sound6 = NULL;

	endwin();
}

void
gpioStateChecker()
{
	int event;
	while (appIsRunning) {
		event = getch();
		if (event != -1)
			keyEventQueue.push(event);		
	}
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	thread keyChecker(gpioStateChecker);

	int event;
	while (appIsRunning) {
		while (!keyEventQueue.empty()) {
			event = keyEventQueue.front();
			keyEventQueue.pop();
			EventHandler(event);
		}

		Update();
	}


	keyChecker.join();

	CleanUp();

	return 0;
}
