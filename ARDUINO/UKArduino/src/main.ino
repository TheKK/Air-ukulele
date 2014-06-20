#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

int isShack = 0;
int isFlex = 0;

void setup()
{
	Serial.begin(9600);
	UKmpu_Setup();
	radio_Setup();
}

void loop()
{
	isShack = UKmpu();
	if (isShack == 1)
		radio_SendData('C');

	isFlex = UKflex();
	if (isFlex == 1)
		radio_SendData('Q');
	else if (isFlex == 2)
		radio_SendData('W');
	else if (isFlex == 3)
		radio_SendData('E');
	else if (isFlex == 4)
		radio_SendData('R');
}

