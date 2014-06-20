int flexSensorPin0 = A3;	// da mu zi
int flexSensorPin1 = A0;	// shi zi
int flexSensorPin2 = A1;	// zong zi
int flexSensorPin3 = A2;	// wu min zi

int flexSensorReading0 = analogRead(flexSensorPin0); 
int flexSensorReading1 = analogRead(flexSensorPin1);
int flexSensorReading2 = analogRead(flexSensorPin2);
int flexSensorReading3 = analogRead(flexSensorPin3);

int flexrate0;
int flexrate1;
int flexrate2;
int flexrate3;

int toggle[4] = {0};
int benchMark = 40;
int returnValue = 0;


int UKflex()
{
	//*****start get flexsensor's status
	flexSensorReading0 = analogRead(flexSensorPin0); 
	flexSensorReading1 = analogRead(flexSensorPin1);
	flexSensorReading2 = analogRead(flexSensorPin2);
	flexSensorReading3 = analogRead(flexSensorPin3);

	flexrate0 = map(flexSensorReading0, 250, 500, 0, 100);
	flexrate1 = map(flexSensorReading1, 250, 500, 0, 100);
	flexrate2 = map(flexSensorReading2, 280, 500, 0, 100);
	flexrate3 = map(flexSensorReading3, 220, 500, 0, 100);

	returnValue = 0;
	//*****finish get the % of flex sensor

	//*****start to reset toggle
	if(flexrate0 >= benchMark && toggle[0] == 1)
		toggle[0] = 0;
	if(flexrate1 >= benchMark && toggle[1] == 1){
		toggle[1] = 0;
		return 5;
	}
	if(flexrate2 >= benchMark && toggle[2] == 1)
		toggle[2] = 0;
	if(flexrate3 >= benchMark && toggle[3] == 1)
		toggle[3] = 0;
	//*****finish reset toggle signal

	//*****start to flex sensor buf write and toggle status
	if(flexrate0 < benchMark && toggle[0] == 0){
		toggle[0] = 1;
		returnValue = 1;
	}
	else if(flexrate1 < benchMark && toggle[1] == 0){
		toggle[1] = 1;
		returnValue = 2;
	}
	else if(flexrate2 < benchMark && toggle[2] == 0){
		toggle[2] = 1;
		returnValue = 3;
	}
	else if(flexrate3 < benchMark && toggle[3] == 0){
		toggle[3] = 1;
		returnValue = 4;
	}
	//***********end flex sensor buf write and toggle status

	return returnValue;
}

