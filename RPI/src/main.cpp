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

enum ApplicationMode
{
	APP_NORMAL_MODE = 0x01,
	APP_HAPPY_MODE,
	APP_SPECIAL_MODE
} appMode;

enum SoundSet
{
	SOUNDSET_NORMAL = 0x00
};

//Normal mode variables
int restartCounter = 0;
int specialCounter = 0;

//Happy mode variables
int happyCount = 0;

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

Chord* normalChord[4];
Sound* happySound;
Sound* specialSound;

NRF24* radio;

int
Init()
{
	wiringPiSetup();

	radio = new NRF24(0, 40, 4000000, 10, 6);

	if (SoundEngine::Init() < 0)
		return 1;

	normalChord[0] = new Chord(
			"./sound/audio/Q0.wav",
			"./sound/audio/Q1.wav",
			"./sound/audio/Q2.wav",
			"./sound/audio/Q3.wav",
			"./sound/audio/Q4.wav",
			"./sound/audio/Q5.wav"
			);

	normalChord[1] = new Chord(
			"./sound/audio/W0.wav",
			"./sound/audio/W1.wav",
			"./sound/audio/W2.wav",
			"./sound/audio/W3.wav",
			"./sound/audio/W4.wav",
			"./sound/audio/W5.wav"
			);

	normalChord[2] = new Chord(
			"./sound/audio/E0.wav",
			"./sound/audio/E1.wav",
			"./sound/audio/E2.wav",
			"./sound/audio/E3.wav",
			"./sound/audio/E4.wav",
			"./sound/audio/E5.wav"
			);

	normalChord[3] = new Chord(
			"./sound/audio/R0.wav",
			"./sound/audio/R1.wav",
			"./sound/audio/R2.wav",
			"./sound/audio/R3.wav",
			"./sound/audio/R4.wav",
			"./sound/audio/R5.wav"
			);

	happySound = new Sound("./sound/happyMode.wav");
	specialSound = new Sound("./sound/audio/special.wav");

	appMode = APP_NORMAL_MODE;

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
NormalEventHandler(enum EventType eventType)
{
	switch (eventType) {
		// String 1
		case two_IS_PRESSED:
			normalChord[0]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 1\n");
			break;
		case three_IS_PRESSED:
			normalChord[0]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 1\n");
			break;
		case four_IS_PRESSED:
			normalChord[0]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 1\n");
			break;
		case seven_IS_PRESSED:
			normalChord[0]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 1\n");
			break;
		case eight_IS_PRESSED:
			normalChord[0]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 1\n");
			break;
		case nine_IS_PRESSED:
			normalChord[0]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 1\n");
			break;
		// String 2
		case w_IS_PRESSED:
			normalChord[1]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 2\n");
			break;
		case e_IS_PRESSED:
			normalChord[1]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 2\n");
			break;
		case r_IS_PRESSED:
			normalChord[1]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 2\n");
			break;
		case u_IS_PRESSED:
			normalChord[1]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 2\n");
			break;
		case i_IS_PRESSED:
			normalChord[1]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 2\n");
			break;
		case o_IS_PRESSED:
			normalChord[1]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 2\n");
			break;
		// String 3
		case s_IS_PRESSED:
			normalChord[2]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 3\n");
			break;
		case d_IS_PRESSED:
			normalChord[2]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 3\n");
			break;
		case f_IS_PRESSED:
			normalChord[2]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 3\n");
			break;
		case j_IS_PRESSED:
			normalChord[2]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 3\n");
			break;
		case k_IS_PRESSED:
			normalChord[2]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 3\n");
			break;
		case l_IS_PRESSED:
			normalChord[2]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 3\n");
			break;
		// String 4
		case x_IS_PRESSED:
			normalChord[3]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 4\n");
			break;
		case c_IS_PRESSED:
			normalChord[3]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 4\n");
			break;
		case v_IS_PRESSED:
			normalChord[3]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 4\n");
			break;
		case m_IS_PRESSED:
			normalChord[3]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 4\n");
			break;
		case mm_IS_PRESSED:
			normalChord[3]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 4\n");
			break;
		case mmm_IS_PRESSED:
			normalChord[3]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 4\n");
			break;
		// All string
		case SPACE_IS_PRESSED:
			normalChord[0]->Pluck();
			normalChord[1]->Pluck();
			normalChord[2]->Pluck();
			normalChord[3]->Pluck();
			mvprintw(12, 10, "Event: Pluck on all strings\n");
			break;
		// System
		case q_IS_PRESSED:
			appIsRunning = false;
			break;
	}

	// Long press to quit
	if (eventType == eight_IS_PRESSED)
		if (restartCounter++ == 10)
			appIsRunning = false;
	else
		restartCounter == 0;

	// Long press to quit
	if (eventType == three_IS_PRESSED)
		if (specialCounter++ == 10) {
			specialSound->Play();
			specialCounter = 0;
		}
	else
		restartCounter == 0;
}

void
HappyEventHandler(enum EventType eventType)
{
	if (eventType == SPACE_IS_PRESSED) {
		switch (++happyCount) {
			case 1:
				normalChord[0]->PressOnString(1);
				normalChord[0]->Pluck();
				break;
			case 2:
				normalChord[0]->PressOnString(2);
				normalChord[0]->Pluck();
				break;
			case 3:
				normalChord[0]->PressOnString(3);
				normalChord[0]->Pluck();
				break;
			case 4:
				normalChord[0]->PressOnString(4);
				normalChord[0]->Pluck();
				break;
			case 5:
				normalChord[0]->PressOnString(1);
				normalChord[0]->Pluck();
				break;
			case 6:
				normalChord[0]->PressOnString(2);
				normalChord[0]->Pluck();
				break;
			case 7:
				appMode = APP_NORMAL_MODE;
				happyCount = 0;
				secretIsOn = false;
				break;
		}
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
		appMode = APP_HAPPY_MODE;
		happySound->Play();
		mvprintw(30, 10, "SECRET IS ON!!\n");
	}
}

void
CleanUp()
{
	SoundEngine::Quit();

	delete radio;
	radio = NULL;

	delete normalChord[0];
	normalChord[0] = NULL;

	delete normalChord[1];
	normalChord[1] = NULL;
	
	delete normalChord[2];
	normalChord[2] = NULL;

	delete normalChord[3];
	normalChord[3] = NULL;

	delete happySound;
	happySound = NULL;

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
void
Listener()
{
	unsigned char symbol;

	while (appIsRunning) {
		symbol = radio->ReceiveData();
		switch (symbol) {
			case 0:
				break;
			case 'Q':
				keyEventQueue.push(nine_IS_PRESSED);
				break;
			case 'W':
				keyEventQueue.push(o_IS_PRESSED);
				break;
			case 'E':
				keyEventQueue.push(l_IS_PRESSED);
				break;
			case 'R':
				keyEventQueue.push(mmm_IS_PRESSED);
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
		// Main event handler
		while (!keyEventQueue.empty()) {
			event = keyEventQueue.front();
			keyEventQueue.pop();
			switch (appMode) {
				case APP_NORMAL_MODE:
					NormalEventHandler(event);
					break;
				case APP_HAPPY_MODE:
					HappyEventHandler(event);
					break;
			}
		}
		// Handle password
		while (passwdQueue.size() >= 10 && !secretIsOn)
			CodeHandler();
	}

	//Make sure they will get together
	keyChecker.join();
	msgChecker.join();

	CleanUp();

	return 0;
}
