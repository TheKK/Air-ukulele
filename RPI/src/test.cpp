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

//My own classes
#include "soundEngine.h"
#include "gpio.h"
#include "chord.h"

using namespace std;

enum EventType
{
	s_IS_PRESSED = 0,
	d_IS_PRESSED,
	f_IS_PRESSED,
	j_IS_PRESSED,
	k_IS_PRESSED,
	SPACE_IS_PRESSED,

	s_IS_RELEASED,
	d_IS_RELEASED,
	f_IS_RELEASED,
	j_IS_RELEASED,
	k_IS_RELEASED,
	SPACE_IS_RELEASED,
};

bool sKeyIsPressing = false;
bool dKeyIsPressing = false;
bool fKeyIsPressing = false;
bool jKeyIsPressing = false;
bool kKeyIsPressing = false;
bool spaceKeyIsPressing = false;

bool appIsRunning = true;
//queue<enum EventType> keyEventQueue;
queue<enum EventType> keyEventQueue;
Chord chord1("star1.wav", "star2.wav", "star3.wav", "star4.wav", "star5.wav");

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	//Ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, true);

	printw("Let's rock!\n");
	printw("Use s,d,f,j,k,l and space key to make some noise.\n");
	printw("Use 'q' to quit..\n");

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
			break;
		case 'd':
			break;
		case 'f':
			break;
		case 'j':
			break;
		case 'k':
			break;
		case 'l':
			break;
		case ' ':
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

	endwin();
}

void
StateChcker()
{
	int event;
	while (appIsRunning) {
		event = getch();

		switch (event) {
			case 's':
				
				break;
			default:
				sKeyIsPressing = false;
				dKeyIsPressing = false;
				fKeyIsPressing = false;
				jKeyIsPressing = false;
				kKeyIsPressing = false;
				break;
		}
	}
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	thread keyChecker(StateChcker);

	int event;
	while (appIsRunning) {
		while (!keyEventQueue.empty()) {
			event = keyEventQueue.front();
			keyEventQueue.pop();
			EventHandler(event);

			mvprintw(10, 10, "%d\n", event);
			refresh();
		}

		Update();
	}

	//Make sure
	keyChecker.join();

	CleanUp();

	return 0;
}
