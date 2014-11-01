int flexSensorPin[4];
flexSensorPin[0] = A3;  // da mu zi
flexSensorPin[1] = A0;	// shi zi
flexSensorPin[2] = A1;	// zong zi
flexSensorPin[3] = A2;	// wu min zi

int flexSensorRaw[4];
int flexrate[4];
int isBended[4] = {0};

int benchMark = 40;

int
UKisFlex(int which)
{
	flexSensorRaw[which] = analogRead(flexnsorPin[which]); 
	flexrate[which] = map(flexSensorRaw[which], 250, 500, 0, 100);

	if ((flexrate[which] >= benchMark) && (isBended[which] == 1))
		isBended[0] = 0;

    if ((flexrate[which] < benchMark) && (isBended[which] == 0))
        isBended[which] = 1;

	return isBended[which];
}
