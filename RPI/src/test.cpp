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
	q_IS_PRESSED,
	SPACE_IS_PRESSED,
};

bool sKeyIsPressing = false;
bool dKeyIsPressing = false;
bool fKeyIsPressing = false;
bool jKeyIsPressing = false;
bool kKeyIsPressing = false;
bool qKeyIsPressing = false;
bool spaceKeyIsPressing = false;

bool appIsRunning = true;
queue<enum EventType> keyEventQueue;
Chord* chord1;

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	chord1 = new Chord(
			"./sound/sound.wav",
			"./sound/star2.wav",
			"./sound/star3.wav",
			"./sound/star4.wav",
			"./sound/star5.wav"
			);
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
EventHandler(enum EventType eventType)
{
	switch (eventType) {
		case s_IS_PRESSED:
			chord1->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string\n");
			break;
		case d_IS_PRESSED:
			chord1->PressOnString(1);
			mvprintw(12, 10, "Event: Press string 1\n");
			break;
		case f_IS_PRESSED:
			chord1->PressOnString(2);
			mvprintw(12, 10, "Event: Press string 2\n");
			break;
		case j_IS_PRESSED:
			chord1->PressOnString(3);
			mvprintw(12, 10, "Event: Press string 3\n");
			break;
		case k_IS_PRESSED:
			chord1->PressOnString(4);
			mvprintw(12, 10, "Event: Press string 4\n");
			break;
		case q_IS_PRESSED:
			appIsRunning = false;
			break;
		case SPACE_IS_PRESSED:
			chord1->Pluck();
			mvprintw(12, 10, "Event: Pluck\n");
			break;
	}
}

void
CleanUp()
{
	SoundEngine::Quit();

	delete chord1;
	chord1 = NULL;

	endwin();
}

void
StateChcker()
{
	int keyCode;
	while (appIsRunning) {
		//Only read valid value
		keyCode = getch();

		if (keyCode != -1) {
			mvprintw(10, 10, "keyCode: %d\n", keyCode);
			refresh();

			switch (keyCode) {
				case 's':
					keyEventQueue.push(s_IS_PRESSED);
					break;
				case 'd':
					keyEventQueue.push(d_IS_PRESSED);
					break;
				case 'f':
					keyEventQueue.push(f_IS_PRESSED);
					break;
				case 'j':
					keyEventQueue.push(j_IS_PRESSED);
					break;
				case 'k':
					keyEventQueue.push(k_IS_PRESSED);
					break;
				case 'q':
					keyEventQueue.push(q_IS_PRESSED);
					break;
				case ' ':
					keyEventQueue.push(SPACE_IS_PRESSED);
					break;
			}
		}
	}
}

int
main(int argc, char* argv[])
{
	if (Init() < 0)
		return 1;

	thread keyChecker(StateChcker);

	enum EventType event;
	while (appIsRunning) {
		while (!keyEventQueue.empty()) {
			event = keyEventQueue.front();
			keyEventQueue.pop();
			EventHandler(event);
		}
	}

	//Make sure
	keyChecker.join();

	CleanUp();

	return 0;
}
