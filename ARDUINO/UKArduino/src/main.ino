#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

void
setup()
{
	Serial.begin(9600);

	UKflex_setup();
	UKmpu_Setup();
	radio_Setup();
}

void
loop()
{
	if (UKflex_isTriggered(FINGER_THUMB))
		radio_SendData('R');

	if (UKflex_isTriggered(FINGER_INDEX))
		radio_SendData('E');

	if (UKflex_isTriggered(FINGER_MID))
		radio_SendData('W');

	if (UKflex_isTriggered(FINGER_RING))
		radio_SendData('Q');

    if (UKmpu_isShaked()) {
        // Do something here
    }

	delay(20);
}
