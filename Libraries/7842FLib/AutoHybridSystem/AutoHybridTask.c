


// TODO comment
// TODO configure motors
// TODO more user functions
// TODO test coasting







task AutoBaseTask()
{
	bool requirementsMet = false;
	int completeCount = 0;

	while(true)
	{
		AutoDriveBase.isCompleted = false;
		waitUntil(AutoDriveBase.turnOn);

		while(AutoDriveBase.turnOn)
		{

			AutoBaseRunPID();


			if(abs(AutoDriveLeftPID.Error) < AutoDriveBase.completeThreshold && abs(AutoDriveRightPID.Error) < AutoDriveBase.completeThreshold)
			{
				completeCount += AutoDriveBase.loopRate;
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


			//AutoDriveBase.turnOn = !(AutoDriveBase.isCompleted && !AutoDriveBase.brakeMode);
			AutoDriveBase.turnOn = !AutoDriveBase.isCompleted || AutoDriveBase.brakeMode;

			wait1Msec(AutoDriveBase.loopRate);

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
