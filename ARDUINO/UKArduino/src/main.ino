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
    if (UKflex_isTriggered(FINGER_THUMB)){
        radio_SendData('R');
        Serial.println("thumb\n");
    }

    if (UKflex_isTriggered(FINGER_INDEX)) {
        radio_SendData('E');
        Serial.println("index finger\n");
    }

    if (UKflex_isTriggered(FINGER_MID) ){
        radio_SendData('W');
        Serial.println("mid finger\n");
    }

    if (UKflex_isTriggered(FINGER_RING)){
        radio_SendData('Q');
        Serial.println("ring finger\n");
    }

    if (UKmpu_isShaked()) {
        if (UKflex_getStatus(FINGER_THUMB) == UK_PRESSED) {
            radio_SendData('C'); /* Cut */
            Serial.println("Cut\n");
        } else {
            radio_SendData('P'); /* Pluck */
            Serial.println("Pluck\n");
        }

    }

    delay(30);
}
