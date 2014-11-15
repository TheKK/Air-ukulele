enum UKFLEX_FINGERS
{
	FINGER_THUMB = 0,
	FINGER_INDEX,
	FINGER_MID,
	FINGER_RING,

	FINGER_COUNT
};

enum UKFLEX_STATUS
{
    UK_PRESSED = 0x00,
    UK_RELEASED
};

int UKflex_setup();
int UKflex_isTriggered(int which);
int UKflex_getStatus(int which);
