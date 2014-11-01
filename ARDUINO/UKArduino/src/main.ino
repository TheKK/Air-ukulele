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
	UKmpu_Setup();
	radio_Setup();
}

void
loop()
{
	if (UKisFlex(0)) {
		radio_SendData('R');	// da mu zi

	if (UKisFlex(1))
		radio_SendData('E');	// shi zi

	if (UKisFlex(2))
		radio_SendData('W');	// zong zi

	if (UKisFlex(3))
		radio_SendData('Q');	// wu min zi

    if (UKmpu_isShaked()) {
        // Do something here
    }

	delay(20);
}
