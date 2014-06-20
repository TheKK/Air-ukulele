#include "radio.h"
#include "UKmpu.h"
#include "UKflex.h"

int isShack = 0;
int isFlex = 0;

int isCut = 0;
int running = 0;
int gun = 0;

void setup()
{
	Serial.begin(9600);
	UKmpu_Setup();
	radio_Setup();
}

void loop()
{
	isFlex = UKflex();
	if (isFlex == 1){
		radio_SendData('R');	// da mu zi
		running++;
	}
	else if (isFlex == 2){
		radio_SendData('E');	// shi zi
		isCut = 0;
	}
	else if (isFlex == 3){
		radio_SendData('W');	// zong zi
		running++;
		gun++;
	}
	else if (isFlex == 4){
		radio_SendData('Q');	// wu min zi
		running++;
		gun++;
	}
	else if (isFlex == 5){
		if(running > 0)
			running--;
	}
	else if (isFlex == 6)
		isCut = 1;
	else if (isFlex == 7){
		if(running > 0)
			running--;
		if(gun > 0)
			gun--;
	}
	else if (isFlex == 8){
		if(running > 0)
			running--;
		if(gun > 0)
			gun--;
	}



	isShack = UKmpu();
	if (isShack == 1){
		if (gun == 2)
			radio_SendData('G');	// gun
		else if (isCut == 0)
			radio_SendData('P');	// pluck
		else if (isCut == 1)
			radio_SendData('C');	// cut
	}

	if (running == 3){
		radio_SendData('P'); delay(500);
		radio_SendData('C'); delay(250);
		radio_SendData('P'); delay(500);
		radio_SendData('P'); delay(250);
		radio_SendData('C'); delay(250);
		radio_SendData('P');
		running = 0;
	}

	delay(20);
}

