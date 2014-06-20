#include "UKmpu.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int ax, ay, az;
int lock = 0;
int debounce = 0;
int mpuReturn = 0;

int nextTotal = 0;
int preTotal = 0;
int checkTotal = 0;

int UKmpu(){
	mpuReturn = 0;
	accelgyro.getAcceleration(&ax, &ay, &az);
	nextTotal = ax + ay + az;

	checkTotal = (nextTotal - preTotal) > 0 ? (nextTotal - preTotal) : (preTotal - nextTotal);

	if (lock == 0 && preTotal != 0 && debounce == 0 && checkTotal >= 11000){
		lock = 1;
		debounce = 11;
		mpuReturn = 1;
	}
	if (lock == 1 && checkTotal < 11000){
		lock = 0;
	}

	preTotal = nextTotal;

	if(debounce > 0)
		debounce--;

	return mpuReturn;
}

void UKmpu_Setup() {
	// join I2C bus (I2Cdev library doesn't do this automatically)
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
		Wire.begin();
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
		Fastwire::setup(400, true);
	#endif

	// initialize device
	Serial.println("Initializing I2C devices...");
	accelgyro.initialize();

	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

