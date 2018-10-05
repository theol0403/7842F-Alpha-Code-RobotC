

AutoDriveDistance(4, 4, Brake, Block);
AutoTurnDegrees(90, Coast, Pass);


// AutoDriveBase(400,400, Block, Brake);
// AutoDriveBase(400,400, Block, Brake);


struct BaseStruct
{
	tSensors leftEn;
	tSensors rightEn;
	float wheelCircumference;
	float chassisCircumference;

	int maxPower;
	int minPower;


	int wantedLeft;
	int wantedRight;
	bool brakeMode;

	int completeThreshold;
	int completeTime;

	bool turnOn;
	bool isCompleted;
};

BaseStruct AutoDriveBase;
pidStruct AutoDriveBasePID;







void AutoBaseInit(tSensors leftEn, tSensors rightEn, float wheelCircumference, float chassisDiameter, int maxPower, int minPower, float Kp, float Ki, float Kd, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
	AutoDriveBase.leftEn = leftEn;
	AutoDriveBase.rightEn = rightEn;
	AutoDriveBase.wheelCircumference = wheelCircumference;
	AutoDriveBase.chassisCircumference = chassisDiameter * 3.1415926;
	AutoDriveBase.maxPower = maxPower;
	AutoDriveBase.minPower = minPower;


	pidInit(AutoDriveBasePID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
}




void AutoDriveDistance(int wantedLeftInch, int wantedRightInch, bool brakeMode, bool waitUntilCompleted)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.wantedLeft += (wantedLeftInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedRightInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(waitUntilCompleted)
	{
		wait1Msec(100);
		while (!AutoDriveBase.isCompleted)
		{
			wait1Msec(20);
		}
	}
}

void AutoTurnDegrees(int wantedDegrees, bool brakeMode, bool waitUntilCompleted, int forwardBiasInch = 0)
{
	AutoDriveBase.turnOn = true;
	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (-wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.brakeMode = brakeMode;

	if(waitUntilCompleted)
	{
		wait1Msec(100);
		while (!AutoDriveBase.isCompleted)
		{
			wait1Msec(20);
		}
	}
}







task AutoDriveTask()
{
AutoDriveBase.wantedLeft;

}

void AutoDriveInch(int wantedInch)
	{
		int brakePower = DRIVEFORWARDS_BRAKEPOWER; //Power to brake with
	int brakeTime = DRIVEFORWARDS_BRAKETIME; //Time to break for

	float fastKP = DRIVEFORWARDS_FASTKP; //Kp for moving fast towards goal - before 1.5
	//int slowSpeed = DRIVEFORWARDS_SLOWCORRECT; //Speed for correction - before 40

	SensorValue[rightBaseEn] = 0; //Reset base encoder
	SensorValue[leftBaseEn] = 0; //Reset base encoder

	int wantedDegrees = (wantedInch / WHEELCIRCUMFERENCE) * 360; // Calculates Encoder Rotations
	int degreesError = wantedDegrees - ((SensorValue[leftBaseEn] + SensorValue[rightBaseEn])/2); //Figure out error and direction of travel
	int firstError = degreesError; //Used to know the direction of reverse power



	while(abs(degreesError) > DRIVEFORWARDS_PTHRESHOLD) //Fast Towards Goal - Threshold of 50 degrees
	{
		degreesError = wantedDegrees - ((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2);

		motor[left] = degreesError * fastKP;
		motor[right] = degreesError * fastKP;
	}

	if(firstError > 0) //Brake in opposite direction
	{
		motor[left] = -brakePower;
		motor[right] = -brakePower;
	}
	else
	{
		motor[left] = brakePower;
		motor[right] = brakePower;
	}
	wait1Msec(brakeTime); //Brake for Time

	degreesError = wantedDegrees - ((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2);
	/*while(abs(degreesError) > DRIVEFORWARDS_SLOWTHRESHOLD)	//Slow Fine Tune - Threshold of 10 degrees
	{
		degreesError = wantedDegrees - SensorValue[baseEn];

		if(degreesError > 0)
		{
			motor[left] = slowSpeed;
			motor[right] = slowSpeed;
		}
		else
		{
			motor[left] = -slowSpeed;
			motor[right] = -slowSpeed;
		}
	}*/
		motor[left] = 0;
		motor[right] = 0;

		wait1Msec(80); //Removed 120
	}



	void drive(int inch){
//Encoders set to 0
		SensorValue[rightBaseEn] = 0; //Reset base encoder
	  SensorValue[leftBaseEn] = 0;

		int deg = inch / WHEELCIRCUMFERENCE * 360;
//When the average value of the encoders are less than 'deg', run motors.
		while ( abs((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2) < abs(deg)-100)
		{
//If the specified distance is positive, run the motors forward...
			if (inch > 0){
				motor[right] = 40;
				motor[left] = 40;
			} else {
//... otherwise, run them backwards.
				motor[right] = -40;
				motor[left] = -40;
			}
		}
//Once the encoders have reached the desired distance, stop.
		if (inch > 0) {
			motor[right] = -10;
			motor[left] = -10;
		} else {
			motor[right] = 10;
			motor[left] = 10;
		}
		wait1Msec(100);
		motor[right] = 0;
		motor[left] = 0;

//Finally, turn off the motors.
	}


	void driveForTime(int power, int time){

		motor[right] = power;
		motor[left] = power;

		wait1Msec(time);

		motor[right] = 0;
		motor[left] = 0;
	}
