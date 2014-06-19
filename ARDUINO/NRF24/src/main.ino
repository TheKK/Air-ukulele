#include "radio.h"
#include "UKmpu.h"

//***************************************************


//***************************************************
void setup()
{
	Serial.begin(9600);
	radio_Setup();
	UKmpu_Setup();
}

void loop()
{
	radio_SendData('c');
	UKmpu();
}

