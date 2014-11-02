#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

void
setup()
{
	Serial.begin(9600);

	UKflex_init();
	UKmpu_Setup();
	radio_Setup();
}

void
loop()
{
	if (UKflex_isBended(THUMB))
		radio_SendData('R');

	if (UKflex_isBended(INDEX_FINGER))
		radio_SendData('E');

	if (UKflex_isBended(MID_FINGER))
		radio_SendData('W');

	if (UKflex_isBended(RING_FINGER))
		radio_SendData('Q');

    if (UKmpu_isShaked()) {
        // Do something here
    }

	delay(20);
}
