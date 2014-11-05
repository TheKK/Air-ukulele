#include "UKflex.h"

int flexSensorPin[FINGER_COUNT];
int isBended[FINGER_COUNT] = {0};

int flexSensorRaw;
int flexrate;
int threshold = 60;

int
UKflex_setup()
{
	flexSensorPin[FINGER_THUMB] =	A3;
	flexSensorPin[FINGER_INDEX] =	A0;
	flexSensorPin[FINGER_MID] =	A1;
	flexSensorPin[FINGER_RING] =	A2;
}

int
UKflex_isTriggered(int which)
{
	flexSensorRaw = analogRead(flexSensorPin[which]);
	flexrate = map(flexSensorRaw, 250, 500, 0, 100);

	// You triggered
	if ((flexrate >= threshold) && (isBended[which] == 0)) {
		isBended[which] = 1;
		return 1;
	}

	if ((flexrate < threshold) && (isBended[which] == 1))
		isBended[which] = 0;

	return 0;
}
