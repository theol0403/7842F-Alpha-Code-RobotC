

// AutoDriveDistance(4, 4, b_Brake, b_Block);
// AutoTurnDegrees(90, b_Coast, b_Pass);


// AutoDriveBase(400,400, b_Block, b_Brake);
// AutoDriveBase(400,400, b_Block, b_Brake);



struct BaseStruct
{
	tSensors leftEn;
	tSensors rightEn;
	float wheelCircumference;
	float chassisCircumference;


	int maxPower;
	int minPower;
	int completeThreshold;
	int completeTime;
	int taskLoopRate;

	int wantedLeft;
	int wantedRight;
	bool brakeMode;


	bool turnOn;
	bool isCompleted;
};



BaseStruct AutoDriveBase;
pidStruct AutoDriveLeftPID;
pidStruct AutoDriveRightPID;


void AutoBaseInit_Chassis(tSensors leftEn, tSensors rightEn, float wheelCircumference, float chassisDiameter)
{
	AutoDriveBase.leftEn = leftEn;
	AutoDriveBase.rightEn = rightEn;
	AutoDriveBase.wheelCircumference = wheelCircumference;
	AutoDriveBase.chassisCircumference = chassisDiameter * 3.1415926;

	AutoDriveBase.wantedLeft = SensorValue[leftEn];
	AutoDriveBase.wantedRight = SensorValue[rightEn];
	AutoDriveBase.brakeMode = false;

	AutoDriveBase.turnOn = false;
	AutoDriveBase.isCompleted = false;

}

void AutoBaseInit_PID(int maxPower, int minPower, int completeThreshold, int completeTime, float Kp, float Ki, float Kd, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
	AutoDriveBase.maxPower = maxPower;
	AutoDriveBase.minPower = minPower;

	AutoDriveBase.completeThreshold = completeThreshold;
	AutoDriveBase.completeTime = completeTime;
	AutoDriveBase.taskLoopRate = 20;


	pidInit(AutoDriveLeftPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
	pidInit(AutoDriveRightPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
}




void AutoBaseDriveDistance(int wantedLeftInch, int wantedRightInch, bool brakeMode = true, bool blockMode = true)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.wantedLeft += (wantedLeftInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedRightInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		wait1Msec(20);
		while (!AutoDriveBase.isCompleted)
		{
			wait1Msec(20);
		}
	}
}

void AutoBaseTurnDegrees(int wantedDegrees, bool brakeMode = true, bool blockMode = true, int forwardBiasInch = 0)
{
	AutoDriveBase.turnOn = true;
	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (wantedTicks) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (-wantedTicks) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		wait1Msec(100);
		while (!AutoDriveBase.isCompleted)
		{
			wait1Msec(20);
		}
	}
}


int AutoBaseLimitPower(int wantedPower)
{
	if(abs(wantedPower) > AutoDriveBase.maxPower) wantedPower = sgn(wantedPower) * AutoDriveBase.maxPower;

	if(abs(wantedPower) < AutoDriveBase.minPower)
	{
		if(abs(wantedPower) < 5)
		{
			wantedPower = 0;
		}
		else
		{
			wantedPower = sgn(wantedPower) * AutoDriveBase.minPower;
		}
	}


	return wantedPower;
}

void AutoBaseRunPID()
{
	int leftPower;
	int rightPower;

	leftPower = pidCalculate(AutoDriveLeftPID, AutoDriveBase.wantedLeft, SensorValue[AutoDriveBase.leftEn]);
	rightPower = pidCalculate(AutoDriveRightPID, AutoDriveBase.wantedRight, SensorValue[AutoDriveBase.rightEn]);

	leftPower = AutoBaseLimitPower(leftPower);
	rightPower = AutoBaseLimitPower(rightPower);

	setBasePower(leftPower, rightPower);
}


bool requirementsMet = false;
int completeCount = 0;
task AutoBaseTask()
{
	while(true)
	{

		waitUntil(AutoDriveBase.turnOn);

		while(AutoDriveBase.turnOn)
		{

			AutoBaseRunPID();


			if(abs(AutoDriveLeftPID.Error) < AutoDriveBase.completeThreshold && abs(AutoDriveRightPID.Error) < AutoDriveBase.completeThreshold)
			{
				completeCount += AutoDriveBase.taskLoopRate;
			}
			else
			{
				completeCount = 0;
			}

			if(completeCount > AutoDriveBase.completeTime)
			{
				AutoDriveBase.isCompleted = true;
			}
			else
			{
				AutoDriveBase.isCompleted = false;
			}


			AutoDriveBase.turnOn = !(AutoDriveBase.isCompleted && !AutoDriveBase.brakeMode);

			wait1Msec(AutoDriveBase.taskLoopRate);

		}

		setBasePower(0, 0);

	}
}


//
// void AutoDriveInch(int wantedInch)
// 	{
// 		int brakePower = DRIVEFORWARDS_BRAKEPOWER; //Power to b_Brake with
// 	int brakeTime = DRIVEFORWARDS_BRAKETIME; //Time to break for
//
// 	float fastKP = DRIVEFORWARDS_FASTKP; //Kp for moving fast towards goal - before 1.5
// 	//int slowSpeed = DRIVEFORWARDS_SLOWCORRECT; //Speed for correction - before 40
//
// 	SensorValue[rightBaseEn] = 0; //Reset base encoder
// 	SensorValue[leftBaseEn] = 0; //Reset base encoder
//
// 	int wantedDegrees = (wantedInch / WHEELCIRCUMFERENCE) * 360; // Calculates Encoder Rotations
// 	int degreesError = wantedDegrees - ((SensorValue[leftBaseEn] + SensorValue[rightBaseEn])/2); //Figure out error and direction of travel
// 	int firstError = degreesError; //Used to know the direction of reverse power
//
//
//
// 	while(abs(degreesError) > DRIVEFORWARDS_PTHRESHOLD) //Fast Towards Goal - Threshold of 50 degrees
// 	{
// 		degreesError = wantedDegrees - ((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2);
//
// 		motor[left] = degreesError * fastKP;
// 		motor[right] = degreesError * fastKP;
// 	}
//
// 	if(firstError > 0) //b_Brake in opposite direction
// 	{
// 		motor[left] = -brakePower;
// 		motor[right] = -brakePower;
// 	}
// 	else
// 	{
// 		motor[left] = brakePower;
// 		motor[right] = brakePower;
// 	}
// 	wait1Msec(brakeTime); //b_Brake for Time
//
// 	degreesError = wantedDegrees - ((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2);
// 	/*while(abs(degreesError) > DRIVEFORWARDS_SLOWTHRESHOLD)	//Slow Fine Tune - Threshold of 10 degrees
// 	{
// 		degreesError = wantedDegrees - SensorValue[baseEn];
//
// 		if(degreesError > 0)
// 		{
// 			motor[left] = slowSpeed;
// 			motor[right] = slowSpeed;
// 		}
// 		else
// 		{
// 			motor[left] = -slowSpeed;
// 			motor[right] = -slowSpeed;
// 		}
// 	}*/
// 		motor[left] = 0;
// 		motor[right] = 0;
//
// 		wait1Msec(80); //Removed 120
// 	}
//
//
//
// 	void drive(int inch){
// //Encoders set to 0
// 		SensorValue[rightBaseEn] = 0; //Reset base encoder
// 	  SensorValue[leftBaseEn] = 0;
//
// 		int deg = inch / WHEELCIRCUMFERENCE * 360;
// //When the average value of the encoders are less than 'deg', run motors.
// 		while ( abs((SensorValue[rightBaseEn]+SensorValue[leftBaseEn])/2) < abs(deg)-100)
// 		{
// //If the specified distance is positive, run the motors forward...
// 			if (inch > 0){
// 				motor[right] = 40;
// 				motor[left] = 40;
// 			} else {
// //... otherwise, run them backwards.
// 				motor[right] = -40;
// 				motor[left] = -40;
// 			}
// 		}
// //Once the encoders have reached the desired distance, stop.
// 		if (inch > 0) {
// 			motor[right] = -10;
// 			motor[left] = -10;
// 		} else {
// 			motor[right] = 10;
// 			motor[left] = 10;
// 		}
// 		wait1Msec(100);
// 		motor[right] = 0;
// 		motor[left] = 0;
//
// //Finally, turn off the motors.
// 	}
//
//
// 	void driveForTime(int power, int time){
//
// 		motor[right] = power;
// 		motor[left] = power;
//
// 		wait1Msec(time);
//
// 		motor[right] = 0;
// 		motor[left] = 0;
// 	}
