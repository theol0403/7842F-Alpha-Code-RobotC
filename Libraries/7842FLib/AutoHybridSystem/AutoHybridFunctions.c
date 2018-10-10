


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








void AutoBaseDriveDistance(float wantedInch, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.lastDistance = wantedInch;

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
	AutoDriveBase.lastDistance = (wantedLeftInch + wantedRightInch)/2;

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
	AutoDriveBase.lastDegrees = wantedDegrees;

	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (-wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
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
