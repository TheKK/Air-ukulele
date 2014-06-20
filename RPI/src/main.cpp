/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: main.cpp
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
#include <wiringPi.h>
#include <wiringPiSPI.h>
}

//My own classes
#include "soundEngine.h"
#include "chord.h"
#include "spi.h"

using namespace std;

enum EventType
{
	s_IS_PRESSED = 0x01,
	d_IS_PRESSED,
	f_IS_PRESSED,
	j_IS_PRESSED,
	k_IS_PRESSED,
	q_IS_PRESSED,
	MSG_IS_C,
	MSG_IS_L,
	SPACE_IS_PRESSED
};

bool appIsRunning = true;
queue<enum EventType> keyEventQueue;

NRF24 radio(0, 40, 4000000, 10, 6);

Chord* chord1;
Chord* chord2;
Chord* chord3;
Chord* chord4;

int
Init()
{
	wiringPiSetup();

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
		case MSG_IS_C:
			chord1->Pluck();
			mvprintw(12, 10, "Event: 'C' from outer space\n");
			break;
		case MSG_IS_L:
			mvprintw(12, 10, "Event: 'L' from outer space\n");
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

void
Listener()
{
	unsigned char symbol;

	while (appIsRunning) {
		symbol = radio.ReceiveData();
		switch (symbol) {
			case 0:
				break;
			case 'C':
				keyEventQueue.push(MSG_IS_C);
				break;
			case 'L':
				keyEventQueue.push(MSG_IS_L);
				break;
			default:
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
	thread msgChecker(Listener);

	enum EventType event;
	while (appIsRunning) {
		while (!keyEventQueue.empty()) {
			event = keyEventQueue.front();
			keyEventQueue.pop();
			EventHandler(event);
		}
	}

	//Make sure they will get together
	keyChecker.join();
	msgChecker.join();

	CleanUp();

	return 0;
}
