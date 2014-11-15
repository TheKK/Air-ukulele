#include "UKflex.h"

#define THRESHOLD   60

int flexSensorPin[FINGER_COUNT];
int isBended[FINGER_COUNT] = {0};
int startFlexRate[FINGER_COUNT] = {0};

int flexSensorRaw;
int flexrate;

int
UKflex_setup()
{
	flexSensorPin[FINGER_THUMB] = A3;
	flexSensorPin[FINGER_INDEX] = A0;
	flexSensorPin[FINGER_MID] =	A1;
	flexSensorPin[FINGER_RING] = A2;

    for (int i = 0; i < FINGER_RING; i++) {
        flexSensorRaw = analogRead(flexSensorPin[i]);
        flexrate = map(flexSensorRaw, 500, 750, 0, 100);

        startFlexRate[i] =  flexrate;
    }
}

int
UKflex_isTriggered(int which)
{
	flexSensorRaw = analogRead(flexSensorPin[which]);
	flexrate = map(flexSensorRaw, 500, 750, 0, 100);

	// You triggered
	if ((flexrate > (startFlexRate[which] + THRESHOLD)) && (isBended[which] == 0)) {
		isBended[which] = 1;
		return 1;
	}

	if ((flexrate < (startFlexRate[which] + THRESHOLD)) && (isBended[which] == 1))
		isBended[which] = 0;

	return 0;
}

int
UKflex_getStatus(int which)
{
    return isBended[which];
}
