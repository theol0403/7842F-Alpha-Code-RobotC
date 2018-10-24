


void AutoBaseWaitUntilComplete(int maxTime = 5000)
{
	wait1Msec(AutoDriveBase.loopRate * 2);
	int emergencyCount = 0;
	while(!AutoDriveBase.isCompleted && emergencyCount < abs(maxTime))
	{
		emergencyCount += AutoDriveBase.loopRate;
		wait1Msec(AutoDriveBase.loopRate);
	}
}


void AutoBaseWaitUntilTickCrossed(int wantedLeft, int wantedRight, int maxTime = 5000)
{
	wait1Msec(AutoDriveBase.loopRate * 2);

	bool leftDirection = (SensorValue[AutoDriveBase.leftEn] < wantedLeft);
	bool rightDirection = (SensorValue[AutoDriveBase.leftEn] < wantedRight);

	bool isLeftCompleted = false;
	bool isRightCompleted = false;
	bool isCompleted = false;

	int emergencyCount = 0;
	while(!isCompleted && emergencyCount < abs(maxTime))
	{

		isLeftCompleted = leftDirection ? (SensorValue[AutoDriveBase.leftEn] > wantedLeft) : (SensorValue[AutoDriveBase.leftEn] < wantedLeft);
		isRightCompleted = rightDirection ? (SensorValue[AutoDriveBase.rightEn] > wantedRight) : (SensorValue[AutoDriveBase.rightEn] < wantedRight);
		isCompleted = (isLeftCompleted && isRightCompleted);

		emergencyCount += AutoDriveBase.loopRate;
		wait1Msec(AutoDriveBase.loopRate);
	}
}




void AutoBaseWaitUntilDistance(float waitInch, int maxTime = 5000)
{
	int wantedLeft = AutoDriveBase.lastWantedLeft + (waitInch / AutoDriveBase.wheelCircumference) * 360;
	int wantedRight = AutoDriveBase.lastWantedRight + (waitInch / AutoDriveBase.wheelCircumference) * 360;

	bool exit;
	if(waitInch > 0)
	{
		if(SensorValue[AutoDriveBase.leftEn] > wantedLeft) exit = true;
		if(SensorValue[AutoDriveBase.rightEn] > wantedRight) exit = true;
	}
	else
	{
		if(SensorValue[AutoDriveBase.leftEn] < wantedLeft) exit = true;
		if(SensorValue[AutoDriveBase.rightEn] < wantedRight) exit = true;
	}

	if(!exit)
	{
		AutoBaseWaitUntilTickCrossed(wantedLeft, wantedRight, maxTime);
	}
}


// void AutoBaseWaitUntilDegrees(float waitDegrees, int maxTime = 5000)
// {
// 	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * waitDegrees;
// 	int wantedLeft = AutoDriveBase.lastWantedLeft + (AutoDriveBase.chosenSide * -wantedTicks/2);
// 	int wantedRight = AutoDriveBase.lastWantedRight + (AutoDriveBase.chosenSide * wantedTicks/2);
//
// 	bool direction = (waitDegrees > 0);
// 	if(AutoDriveBase.chosenSide == blueSide) direction = !direction;
// 	if(direction)
// 	{
// 		if(SensorValue[AutoDriveBase.leftEn] < wantedLeft) return;
// 		if(SensorValue[AutoDriveBase.rightEn] > wantedRight) return;
// 	}
// 	else
// 	{
// 		if(SensorValue[AutoDriveBase.leftEn] > wantedLeft) return;
// 		if(SensorValue[AutoDriveBase.rightEn] < wantedRight) return;
// 	}
//
// 	AutoBaseWaitUntilTickCrossed(wantedLeft, wantedRight, maxTime);
// }








void AutoBaseDriveDistance(float wantedInch, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.baseMode = baseDrive;
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastWantedLeft = AutoDriveBase.wantedLeft;
	AutoDriveBase.lastWantedRight = AutoDriveBase.wantedRight;

	AutoDriveBase.wantedLeft += (wantedInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		AutoBaseWaitUntilComplete(AutoDriveBase.emgInchTimeP * abs(wantedInch));
		AutoDriveBase.wantedLeft = 0;
		AutoDriveBase.wantedRight = 0;
		SensorValue[AutoDriveBase.leftEn] = 0;
		SensorValue[AutoDriveBase.rightEn] = 0;
	}



}


void AutoBaseDriveChassis(float wantedLeftInch, float wantedRightInch, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.baseMode = baseDrive;
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastWantedLeft = AutoDriveBase.wantedLeft;
	AutoDriveBase.lastWantedRight = AutoDriveBase.wantedRight;

	AutoDriveBase.wantedLeft += (wantedLeftInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedRightInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
    float longestStep = abs(wantedLeftInch) > abs(wantedRightInch) ? abs(wantedLeftInch) : abs(wantedRightInch);
		AutoBaseWaitUntilComplete(AutoDriveBase.emgInchTimeP * longestStep);
		AutoDriveBase.wantedLeft = SensorValue[AutoDriveBase.leftEn];
		AutoDriveBase.wantedRight = SensorValue[AutoDriveBase.rightEn];
	}

}

void AutoBaseTurnDegrees(float wantedDegrees, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.baseMode = baseTurn;
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastWantedLeft = AutoDriveBase.wantedLeft;
	AutoDriveBase.lastWantedRight = AutoDriveBase.wantedRight;

	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (-(wantedTicks/2));
	AutoDriveBase.wantedRight += ((wantedTicks/2));
	AutoDriveBase.brakeMode = brakeMode;

  if(blockMode)
	{
    AutoBaseWaitUntilComplete(AutoDriveBase.emgDegTimeP * abs(wantedDegrees));
		AutoDriveBase.wantedLeft = 0;
		AutoDriveBase.wantedRight = 0;
		SensorValue[AutoDriveBase.leftEn] = 0;
		SensorValue[AutoDriveBase.rightEn] = 0;
	}

}


void AutoBaseDriveAllign(int wantedInch, int maxTime, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.baseMode = baseAllign;
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastWantedLeft = AutoDriveBase.wantedLeft;
	AutoDriveBase.lastWantedRight = AutoDriveBase.wantedRight;

	AutoDriveBase.wantedLeft += (wantedInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		AutoBaseWaitUntilComplete(maxTime);
	}


	AutoDriveBase.wantedLeft = 0;
	AutoDriveBase.wantedRight = 0;
	SensorValue[AutoDriveBase.leftEn] = 0;
	SensorValue[AutoDriveBase.rightEn] = 0;

}






int AutoBaseLimitPower(int wantedPower)
{
	if(abs(wantedPower) > AutoDriveBase.maxPower[AutoDriveBase.baseMode]) wantedPower = sgn(wantedPower) * AutoDriveBase.maxPower[AutoDriveBase.baseMode];

	if(abs(wantedPower) < AutoDriveBase.minPower[AutoDriveBase.baseMode])
	{
		if(abs(wantedPower) < 5)
		{
			wantedPower = 0;
		}
		else
		{
			wantedPower = sgn(wantedPower) * AutoDriveBase.minPower[AutoDriveBase.baseMode];
		}
	}
	return wantedPower;
}


void setBasePower(int leftSpeed, int rightSpeed);

void AutoBaseRunPID()
{
	int leftPower;
	int rightPower;

	leftPower = pidCalculate(AutoDriveBase.autoBasePID[0][AutoDriveBase.baseMode], AutoDriveBase.wantedLeft, SensorValue[AutoDriveBase.leftEn]);
	rightPower = pidCalculate(AutoDriveBase.autoBasePID[1][AutoDriveBase.baseMode], AutoDriveBase.wantedRight, SensorValue[AutoDriveBase.rightEn]);

	leftPower = AutoBaseLimitPower(leftPower);
	rightPower = AutoBaseLimitPower(rightPower);

	setBasePower(leftPower, rightPower);
}
