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
	SOUNDSET_NORMAL = 0x00,
	SOUNDSET_SPECIAL
};

//Normal mode variables
int restartCounter = 0;
int specialCounter = 0;

//Happy mode variables
int happyCount = 0;

enum EventType
{
	// String 1
	STRING1_RELEASE = 0x01,
	STRING1_POS1_PRESS,
	STRING1_POS2_PRESS,
	STRING1_POS3_PRESS,
	STRING1_POS4_PRESS,
	STRING1_POS5_PRESS,
	STRING1_PLUCK,

	// String 2
	STRING2_RELEASE,
	STRING2_POS1_PRESS,
	STRING2_POS2_PRESS,
	STRING2_POS3_PRESS,
	STRING2_POS4_PRESS,
	STRING2_POS5_PRESS,
	STRING2_PLUCK,

	// String 3
	STRING3_RELEASE,
	STRING3_POS1_PRESS,
	STRING3_POS2_PRESS,
	STRING3_POS3_PRESS,
	STRING3_POS4_PRESS,
	STRING3_POS5_PRESS,
	STRING3_PLUCK,

	// String 4
	STRING4_RELEASE,
	STRING4_POS1_PRESS,
	STRING4_POS2_PRESS,
	STRING4_POS3_PRESS,
	STRING4_POS4_PRESS,
	STRING4_POS5_PRESS,
	STRING4_PLUCK,

	// Code
	UP_IS_PRESSED,
	DOWN_IS_PRESSED,
	LEFT_IS_PRESSED,
	RIGHT_IS_PRESSED,
	a_IS_PRESSED,
	b_IS_PRESSED,

	// System
	QUIT_IS_PRESENT,
	PLUCK_IS_PRESENT,
	CUT_IS_PRESENT
};

bool appIsRunning = true;
queue<enum EventType> keyEventQueue;

bool secretIsOn = false;
queue<enum EventType> passwdQueue;

#define NUMBER_OF_STRING	4
Chord* currentChord[NUMBER_OF_STRING];
Chord* normalChord[NUMBER_OF_STRING];

Sound* cutSound;
Sound* happySound;
Sound* specialSound;

NRF24* radio;

void
ChangeSoundset(enum SoundSet set)
{
	switch (set) {
		case SOUNDSET_NORMAL:
			for (int i = 0; i < NUMBER_OF_STRING; i++)
				currentChord[i] = normalChord[i];
			break;
		case SOUNDSET_SPECIAL:
			break;
	}
}

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

	ChangeSoundset(SOUNDSET_NORMAL);

	cutSound = new Sound("./sound/audio/cut.wav");
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
		case STRING1_RELEASE:
			currentChord[0]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 1\n");
			break;
		case STRING1_POS1_PRESS:
			currentChord[0]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 1\n");
			break;
		case STRING1_POS2_PRESS:
			currentChord[0]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 1\n");
			break;
		case STRING1_POS3_PRESS:
			currentChord[0]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 1\n");
			break;
		case STRING1_POS4_PRESS:
			currentChord[0]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 1\n");
			break;
		case STRING1_PLUCK:
			currentChord[0]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 1\n");
			break;
		// String 2
		case STRING2_RELEASE:
			currentChord[1]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 2\n");
			break;
		case STRING2_POS1_PRESS:
			currentChord[1]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 2\n");
			break;
		case STRING2_POS2_PRESS:
			currentChord[1]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 2\n");
			break;
		case STRING2_POS3_PRESS:
			currentChord[1]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 2\n");
			break;
		case STRING2_POS4_PRESS:
			currentChord[1]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 2\n");
			break;
		case STRING2_PLUCK:
			currentChord[1]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 2\n");
			break;
		// String 3
		case STRING3_RELEASE:
			currentChord[2]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 3\n");
			break;
		case STRING3_POS1_PRESS:
			currentChord[2]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 3\n");
			break;
		case STRING3_POS2_PRESS:
			currentChord[2]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 3\n");
			break;
		case STRING3_POS3_PRESS:
			currentChord[2]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 3\n");
			break;
		case STRING3_POS4_PRESS:
			currentChord[2]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 3\n");
			break;
		case STRING3_PLUCK:
			currentChord[2]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 3\n");
			break;
		// String 4
		case STRING4_RELEASE:
			currentChord[3]->ReleaseFromString();
			mvprintw(12, 10, "Event: Release string from string 4\n");
			break;
		case STRING4_POS1_PRESS:
			currentChord[3]->PressOnString(1);
			mvprintw(12, 10, "Event: Press position 1 on string 4\n");
			break;
		case STRING4_POS2_PRESS:
			currentChord[3]->PressOnString(2);
			mvprintw(12, 10, "Event: Press position 2 on string 4\n");
			break;
		case STRING4_POS3_PRESS:
			currentChord[3]->PressOnString(3);
			mvprintw(12, 10, "Event: Press position 3 on string 4\n");
			break;
		case STRING4_POS4_PRESS:
			currentChord[3]->PressOnString(4);
			mvprintw(12, 10, "Event: Press position 4 on string 4\n");
			break;
		case STRING4_PLUCK:
			currentChord[3]->Pluck();
			mvprintw(12, 10, "Event: Pluck on string 4\n");
			break;
		// All string
		case PLUCK_IS_PRESENT:
			currentChord[0]->Pluck();
			currentChord[1]->Pluck();
			currentChord[2]->Pluck();
			currentChord[3]->Pluck();
			mvprintw(12, 10, "Event: Pluck on all strings\n");
			break;
		case CUT_IS_PRESENT:
			cutSound->Play();
			mvprintw(12, 10, "Event: Cut on all strings\n");
			break;
		// System
		case QUIT_IS_PRESENT:
			appIsRunning = false;
			break;
	}

	// Long press to quit
	if (eventType == STRING1_POS4_PRESS)
		if (restartCounter++ == 10)
			appIsRunning = false;
	else
		restartCounter == 0;

	// Long press to quit
	if (eventType == STRING1_POS1_PRESS)
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
	if (eventType == PLUCK_IS_PRESENT) {
		switch (++happyCount) {
			case 1:
				currentChord[0]->ReleaseFromString();
				currentChord[1]->PressOnString(1);
				currentChord[2]->ReleaseFromString();
				currentChord[3]->PressOnString(2);

				currentChord[0]->Pluck();
				currentChord[3]->Pluck();
				break;
			case 2:
				currentChord[2]->Pluck();
				break;
			case 3:
				currentChord[0]->Pluck();
				break;
			case 4:
				currentChord[1]->Pluck();
				break;
			case 5:
				currentChord[0]->Pluck();
				currentChord[3]->Pluck();
				break;
			case 6:
				currentChord[2]->Pluck();
				break;
			case 7:
				currentChord[0]->PressOnString(3);
				currentChord[0]->Pluck();
				break;
			case 8:
				currentChord[2]->Pluck();
				break;
			case 9:
				currentChord[0]->PressOnString(3);
				currentChord[1]->ReleaseFromString();
				currentChord[2]->ReleaseFromString();
				currentChord[3]->ReleaseFromString();

				currentChord[0]->Pluck();
				currentChord[3]->Pluck();
				break;
			case 10:
				currentChord[0]->PressOnString(1);

				currentChord[0]->Pluck();
				break;
			case 11:
				currentChord[0]->Pluck();
				break;
			case 12:
				currentChord[0]->ReleaseFromString();

				currentChord[0]->Pluck();
				break;
			case 13:
				currentChord[0]->PressOnString(3);

				currentChord[1]->Pluck();
				currentChord[3]->Pluck();
				break;
			case 14:
				currentChord[2]->Pluck();
				break;
			case 15:
				currentChord[1]->Pluck();
				break;
			case 16:
				currentChord[0]->Pluck();
				break;
			default:
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

	delete specialSound;
	specialSound = NULL;

	delete cutSound;
	cutSound = NULL;

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
					eventType = STRING1_RELEASE;
					break;
				case '3':
					eventType = STRING1_POS1_PRESS;
					break;
				case '4':
					eventType = STRING1_POS2_PRESS;
					break;
				case '7':
					eventType = STRING1_POS3_PRESS;
					break;
				case '8':
					eventType = STRING1_POS4_PRESS;
					break;
				case '9':
					eventType = STRING1_PLUCK;
					break;
				// String 2
				case 'w':
					eventType = STRING2_RELEASE;
					break;
				case 'e':
					eventType = STRING2_POS1_PRESS;
					break;
				case 'r':
					eventType = STRING2_POS2_PRESS;
					break;
				case 'u':
					eventType = STRING2_POS3_PRESS;
					break;
				case 'i':
					eventType = STRING2_POS4_PRESS;
					break;
				case 'o':
					eventType = STRING2_PLUCK;
					break;
				// String 3
				case 's':
					eventType = STRING3_RELEASE;
					break;
				case 'd':
					eventType = STRING3_POS1_PRESS;
					break;
				case 'f':
					eventType = STRING3_POS2_PRESS;
					break;
				case 'j':
					eventType = STRING3_POS3_PRESS;
					break;
				case 'k':
					eventType = STRING3_POS4_PRESS;
					break;
				case 'l':
					eventType = STRING3_PLUCK;
					break;
				// String 4
				case 'x':
					eventType = STRING4_RELEASE;
					break;
				case 'c':
					eventType = STRING4_POS1_PRESS;
					break;
				case 'v':
					eventType = STRING4_POS2_PRESS;
					break;
				case 'm':
					eventType = STRING4_POS3_PRESS;
					break;
				case ',':
					eventType = STRING4_POS4_PRESS;
					break;
				case '.':
					eventType = STRING4_PLUCK;
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
					eventType = QUIT_IS_PRESENT;
					break;
				case ' ':
					eventType = PLUCK_IS_PRESENT;
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
				keyEventQueue.push(STRING1_PLUCK);
				break;
			case 'W':
				keyEventQueue.push(STRING2_PLUCK);
				break;
			case 'E':
				keyEventQueue.push(STRING3_PLUCK);
				break;
			case 'R':
				keyEventQueue.push(STRING4_PLUCK);
				break;
			case 'P':
				keyEventQueue.push(PLUCK_IS_PRESENT);
				break;
			case 'C':
				keyEventQueue.push(CUT_IS_PRESENT);
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
