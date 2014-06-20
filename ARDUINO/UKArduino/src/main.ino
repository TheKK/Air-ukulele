#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

int isShack = 0;
int isFlex = 0;
int isCut = 0;

void setup()
{
	Serial.begin(9600);
	UKmpu_Setup();
	radio_Setup();
}

void loop()
{
	isFlex = UKflex();
	if (isFlex == 1)
		radio_SendData('R');	// da mu zi
	else if (isFlex == 2){
		radio_SendData('E');	// shi zi
		isCut = 0;
	}
	else if (isFlex == 3)
		radio_SendData('W');	// zong zi
	else if (isFlex == 4)
		radio_SendData('Q');	// wu min zi
	else if (isFlex == 5)
		isCut = 1;


	isShack = UKmpu();
	if (isShack == 1){
		if (isCut == 0)
			radio_SendData('P');	// pluck
		else
			radio_SendData('C');	// cut
	}

	delay(20);
}

