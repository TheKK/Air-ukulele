#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

int isShack = 0;
int isFlex = 0;

int isCut = 0;
int running = 0;
int gun = 0;

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
	if (UKflex_isBended(0))
		radio_SendData('R');	// da mu zi

	if (UKflex_isBended(1))
		radio_SendData('E');	// shi zi

	if (UKflex_isBended(2))
		radio_SendData('W');	// zong zi

	if (UKflex_isBended(3))
		radio_SendData('Q');	// wu min zi

    if (UKmpu_isShaked()) {
        // Do something here
    }

	delay(20);
}
