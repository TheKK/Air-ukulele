int flexSensorPin0 = A0; //analog pin 0
int flexSensorPin1 = A1; //analog pin 0
int flexSensorPin2 = A2; //analog pin 0
int flexSensorPin3 = A3; //analog pin 0

int flexSensorReading0 = analogRead(flexSensorPin0); 
int flexSensorReading1 = analogRead(flexSensorPin1);
int flexSensorReading2 = analogRead(flexSensorPin2);
int flexSensorReading3 = analogRead(flexSensorPin3);

int flexrate0 = map(flexSensorReading0, 512, 614, 0, 100);
int flexrate1 = map(flexSensorReading1, 512, 614, 0, 100);
int flexrate2 = map(flexSensorReading2, 512, 614, 0, 100);
int flexrate3 = map(flexSensorReading3, 512, 614, 0, 100);

int toggle[4]={0};
int returnValue = 0;

int UKflex()
{
	//*****start get flexsensor's status
	flexSensorReading0 = analogRead(flexSensorPin0); 
	flexSensorReading1 = analogRead(flexSensorPin1);
	flexSensorReading2 = analogRead(flexSensorPin2);
	flexSensorReading3 = analogRead(flexSensorPin3);

	flexrate0 = map(flexSensorReading0, 512, 614, 0, 100);
	flexrate1 = map(flexSensorReading1, 512, 614, 0, 100);
	flexrate2 = map(flexSensorReading2, 512, 614, 0, 100);
	flexrate3 = map(flexSensorReading3, 512, 614, 0, 100);
	//*****finish get the % of flex sensor

	//*****start to reset toggle
	if( flexrate0 >50)
		toggle[0]=0;
	if( flexrate1 >50)
		toggle[1]=0;
	if( flexrate2 >50)
		toggle[2]=0;
	if( flexrate3 >50)
		toggle[3]=0;
	//*****finish reset toggle signal

	//*****start to flex sensor buf write and toggle status
	if(toggle[0]==toggle[1]==toggle[2]==toggle[3] == 0){
		if(flexrate0<50){
			toggle[0]=1;
			returnValue=1;
		}
		else if(flexrate1<50){
			toggle[1]=1;
			returnValue=2;
		}
		else if(flexrate2<50){
			toggle[2]=1;
			returnValue=3;
		}
		else if(flexrate3<50){
			toggle[3]=1;
			returnValue=4;
		}
		else{
			returnValue=0;
		}
	}
	//***********end flex sensor buf write and toggle status

	return returnValue;
}

