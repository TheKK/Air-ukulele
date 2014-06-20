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
#include "chord.h"

using namespace std;

enum EventType
{
	// String 1
	two_IS_PRESSED = 0x01,
	three_IS_PRESSED,
	four_IS_PRESSED,
	seven_IS_PRESSED,
	eight_IS_PRESSED,
	nine_IS_PRESSED,

	// String 2
	w_IS_PRESSED,
	e_IS_PRESSED,
	r_IS_PRESSED,
	u_IS_PRESSED,
	i_IS_PRESSED,
	o_IS_PRESSED,

	// String 3
	s_IS_PRESSED,
	d_IS_PRESSED,
	f_IS_PRESSED,
	j_IS_PRESSED,
	k_IS_PRESSED,
	l_IS_PRESSED,

	// String 4
	x_IS_PRESSED,
	c_IS_PRESSED,
	v_IS_PRESSED,
	m_IS_PRESSED,
	mm_IS_PRESSED,
	mmm_IS_PRESSED,

	// Code
	UP_IS_PRESSED,
	DOWN_IS_PRESSED,
	LEFT_IS_PRESSED,
	RIGHT_IS_PRESSED,
	a_IS_PRESSED,
	b_IS_PRESSED,

	// System
	q_IS_PRESSED,
	SPACE_IS_PRESSED
};

bool appIsRunning = true;
queue<enum EventType> keyEventQueue;

bool secretIsOn = false;
queue<enum EventType> passwdQueue;

Chord* chord1;
Chord* chord2;
Chord* chord3;
Chord* chord4;

int
Init()
{
	if (SoundEngine::Init() < 0)
		return 1;

	chord1 = new Chord(
			"./sound/audio/Q0.wav",
			"./sound/audio/Q1.wav",
			"./sound/audio/Q2.wav",
			"./sound/audio/Q3.wav",
			"./sound/audio/Q4.wav"
			);

	chord2 = new Chord(
			"./sound/audio/W0.wav",
			"./sound/audio/W1.wav",
			"./sound/audio/W2.wav",
			"./sound/audio/W3.wav",
			"./sound/audio/W4.wav"
			);

	chord3 = new Chord(
			"./sound/audio/E0.wav",
			"./sound/audio/E1.wav",
			"./sound/audio/E2.wav",
			"./sound/audio/E3.wav",
			"./sound/audio/E4.wav"
			);

	chord4 = new Chord(
			"./sound/audio/R0.wav",
			"./sound/audio/R1.wav",
			"./sound/audio/R2.wav",
			"./sound/audio/R3.wav",
			"./sound/audio/R4.wav"
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
		// String 1
		case two_IS_PRESSED:
			chord1->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 1\n");
			break;
		case three_IS_PRESSED:
			chord1->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 1\n");
			break;
		case four_IS_PRESSED:
			chord1->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 1\n");
			break;
		case seven_IS_PRESSED:
			chord1->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 1\n");
			break;
		case eight_IS_PRESSED:
			chord1->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 1\n");
			break;
		case nine_IS_PRESSED:
			chord1->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 1\n");
			break;
		// String 2
		case w_IS_PRESSED:
			chord2->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 2\n");
			break;
		case e_IS_PRESSED:
			chord2->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 2\n");
			break;
		case r_IS_PRESSED:
			chord2->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 2\n");
			break;
		case u_IS_PRESSED:
			chord2->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 2\n");
			break;
		case i_IS_PRESSED:
			chord2->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 2\n");
			break;
		case o_IS_PRESSED:
			chord2->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 2\n");
			break;
		// String 3
		case s_IS_PRESSED:
			chord3->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 3\n");
			break;
		case d_IS_PRESSED:
			chord3->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 3\n");
			break;
		case f_IS_PRESSED:
			chord3->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 3\n");
			break;
		case j_IS_PRESSED:
			chord3->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 3\n");
			break;
		case k_IS_PRESSED:
			chord3->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 3\n");
			break;
		case l_IS_PRESSED:
			chord3->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 3\n");
			break;
		// String 4
		case x_IS_PRESSED:
			chord4->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 4\n");
			break;
		case c_IS_PRESSED:
			chord4->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 4\n");
			break;
		case v_IS_PRESSED:
			chord4->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 4\n");
			break;
		case m_IS_PRESSED:
			chord4->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 4\n");
			break;
		case mm_IS_PRESSED:
			chord4->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 4\n");
			break;
		case mmm_IS_PRESSED:
			chord4->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 4\n");
			break;
		// All string
		case SPACE_IS_PRESSED:
			chord1->Pluck();
			chord2->Pluck();
			chord3->Pluck();
			chord4->Pluck();
			mvprintw(12, 10, "Event: Pluck on all strings\n");
			break;
		// System
		case q_IS_PRESSED:
			appIsRunning = false;
			break;
	}
}

void
CodeHandler()
{
	if (passwdQueue.front() != UP_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != UP_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != DOWN_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != DOWN_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != LEFT_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != RIGHT_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != LEFT_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != RIGHT_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != b_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else
		passwdQueue.pop();

	if (passwdQueue.front() != a_IS_PRESSED) {
		passwdQueue.pop();
		return;
	} else {
		passwdQueue.pop();
		secretIsOn = true;
		mvprintw(30, 10, "SECRET IS ON!!\n");
	}
}

void
CleanUp()
{
	SoundEngine::Quit();

	delete chord1;
	chord1 = NULL;

	delete chord2;
	chord2 = NULL;
	
	delete chord3;
	chord3 = NULL;

	delete chord4;
	chord4 = NULL;

	endwin();
}

void
StateChcker()
{
	int keyCode;
	enum EventType eventType;

	while (appIsRunning) {
		//Only read valid value
		keyCode = getch();

		if (keyCode != -1) {
			mvprintw(10, 10, "keyCode: %d\n", keyCode);
			refresh();

			switch (keyCode) {
				// String 1
				case '2':
					eventType = two_IS_PRESSED;
					break;
				case '3':
					eventType = three_IS_PRESSED;
					break;
				case '4':
					eventType = four_IS_PRESSED;
					break;
				case '7':
					eventType = seven_IS_PRESSED;
					break;
				case '8':
					eventType = eight_IS_PRESSED;
					break;
				case '9':
					eventType = nine_IS_PRESSED;
					break;
				// String 2
				case 'w':
					eventType = w_IS_PRESSED;
					break;
				case 'e':
					eventType = e_IS_PRESSED;
					break;
				case 'r':
					eventType = r_IS_PRESSED;
					break;
				case 'u':
					eventType = u_IS_PRESSED;
					break;
				case 'i':
					eventType = i_IS_PRESSED;
					break;
				case 'o':
					eventType = o_IS_PRESSED;
					break;
				// String 3
				case 's':
					eventType = s_IS_PRESSED;
					break;
				case 'd':
					eventType = d_IS_PRESSED;
					break;
				case 'f':
					eventType = f_IS_PRESSED;
					break;
				case 'j':
					eventType = j_IS_PRESSED;
					break;
				case 'k':
					eventType = k_IS_PRESSED;
					break;
				case 'l':
					eventType = l_IS_PRESSED;
					break;
				// String 4
				case 'x':
					eventType = x_IS_PRESSED;
					break;
				case 'c':
					eventType = c_IS_PRESSED;
					break;
				case 'v':
					eventType = v_IS_PRESSED;
					break;
				case 'm':
					eventType = m_IS_PRESSED;
					break;
				case ',':
					eventType = mm_IS_PRESSED;
					break;
				case '.':
					eventType = mmm_IS_PRESSED;
					break;
				// Code
				case KEY_UP:
					eventType = UP_IS_PRESSED;
					break;
				case KEY_DOWN:
					eventType = DOWN_IS_PRESSED;
					break;
				case KEY_LEFT:
					eventType = LEFT_IS_PRESSED;
					break;
				case KEY_RIGHT:
					eventType = RIGHT_IS_PRESSED;
					break;
				case 'a':
					eventType = a_IS_PRESSED;
					break;
				case 'b':
					eventType = b_IS_PRESSED;
					break;
				// Pluck
				case 'q':
					eventType = q_IS_PRESSED;
					break;
				case ' ':
					eventType = SPACE_IS_PRESSED;
					break;
			}

			keyEventQueue.push(eventType);
			passwdQueue.push(eventType);
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
		// Handle password
		while (passwdQueue.size() >= 10 && !secretIsOn)
			CodeHandler();
	}

	//Make sure they will get together
	keyChecker.join();

	CleanUp();

	return 0;
}
