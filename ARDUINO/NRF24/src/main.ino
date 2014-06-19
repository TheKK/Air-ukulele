#include "radio.h"
#include "UKmpu.h"

//***************************************************
void setup()
{
	Serial.begin(9600);
	UKmpu_Setup();
	radio_Setup();
}

void loop()
{
	int isShack = UKmpu();
	if (isShack == 1)
		radio_SendData('C');
}

