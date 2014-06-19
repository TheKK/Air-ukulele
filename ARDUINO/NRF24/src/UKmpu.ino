#include "UKmpu.h"

void UKmpu(){
	accelgyro.getAcceleration(&ax, &ay, &az);

	if(count % 50 == 0){         
		n = ax;

		if (i == 0 && n - p > 5000){
			Serial.print("send");Serial.print("\n");
			i = 1;
		}
		if (i == 1 && n - p < 5000){
			Serial.print("++++++++++++++++++++");Serial.print("\n");
			i = 0;
		}
		p = ax;
	}
	count++;
}

void UKmpu_Setup() {
	// join I2C bus (I2Cdev library doesn't do this automatically)
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
		Wire.begin();
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
		Fastwire::setup(400, true);
	#endif

	Serial.begin(9600);

	// initialize device
	Serial.println("Initializing I2C devices...");
	accelgyro.initialize();

	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

