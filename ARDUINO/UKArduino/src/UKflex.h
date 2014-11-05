enum UKFLEX_FINGERS
{
	FINGER_THUMB = 0,
	FINGER_INDEX,
	FINGER_MID,
	FINGER_RING,

	FINGER_COUNT
};

int UKflex_setup();
int UKflex_isTriggered(int which);
