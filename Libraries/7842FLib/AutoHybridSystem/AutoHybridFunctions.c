


void AutoBaseWaitUntilComplete(int maxTime = 5000)
{
	int emergencyCount = 0;
	wait1Msec(AutoDriveBase.loopRate * 2);
	while(!AutoDriveBase.isCompleted && emergencyCount < abs(maxTime))
	{
		emergencyCount += AutoDriveBase.loopRate;
		wait1Msec(AutoDriveBase.loopRate);
	}
}


void AutoBaseWaitUntilTicks(bool direction, int leftTicks, int rightTicks, int maxTime = 5000)
{
	wait1Msec(AutoDriveBase.loopRate * 2);
	int emergencyCount = 0;
	bool isCompleted = false;
	while(!isCompleted && emergencyCount < abs(maxTime))
	{
		if(direction)
		{
			isCompleted = ((SensorValue[AutoDriveBase.leftEn] > leftTicks) && (SensorValue[AutoDriveBase.rightEn] > rightTicks));
		}
		else
		{
			isCompleted = ((SensorValue[AutoDriveBase.leftEn] < leftTicks) && (SensorValue[AutoDriveBase.rightEn] < rightTicks));
		}
		emergencyCount += AutoDriveBase.loopRate;
		wait1Msec(AutoDriveBase.loopRate);
	}
}




void AutoBaseWaitUntilDistance(float waitInch, int maxTime = 5000)
{
	int wantedLeft = AutoDriveBase.lastWantedLeft + (waitInch / AutoDriveBase.wheelCircumference) * 360;
	int wantedRight = AutoDriveBase.lastWantedRight + (waitInch / AutoDriveBase.wheelCircumference) * 360;

	AutoBaseWaitUntilTicks(waitInch > 0, wantedLeft, wantedRight, maxTime);
}


void AutoBaseWaitUntilDegree(float waitDegrees, int maxTime = 5000)
{
	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * waitDegrees;
	int wantedLeft = AutoDriveBase.lastWantedLeft + (AutoDriveBase.chosenSide * -wantedTicks/2);
	int wantedRight = AutoDriveBase.lastWantedRight + (AutoDriveBase.chosenSide * wantedTicks/2);

	AutoBaseWaitUntilTicks(waitDegrees > 0, wantedLeft, wantedRight, maxTime);
}








void AutoBaseDriveDistance(float wantedInch, bool blockMode = true, bool brakeMode = true)
{
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
	}

}


void AutoBaseDriveChassis(float wantedLeftInch, float wantedRightInch, bool blockMode = true, bool brakeMode = true)
{
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
	}

}

void AutoBaseTurnDegrees(float wantedDegrees, bool blockMode = true, bool brakeMode = true, float forwardBiasInch = 0)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastWantedLeft = AutoDriveBase.wantedLeft;
	AutoDriveBase.lastWantedRight = AutoDriveBase.wantedRight;

	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (AutoDriveBase.chosenSide * -wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (AutoDriveBase.chosenSide * wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.brakeMode = brakeMode;

  if(blockMode)
	{
    AutoBaseWaitUntilComplete(AutoDriveBase.emgDegTimeP * abs(wantedDegrees));
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


void setBasePower(int leftSpeed, int rightSpeed);

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
