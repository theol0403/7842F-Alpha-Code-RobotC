


void AutoBaseDriveDistance(int wantedLeftInch, int wantedRightInch, bool brakeMode, bool blockMode)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.wantedLeft += (wantedLeftInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedRightInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		wait1Msec(40);
		waitUntil(AutoDriveBase.isCompleted);
	}
}

void AutoBaseTurnDegrees(int wantedDegrees, bool brakeMode, bool blockMode, int forwardBiasInch = 0)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (wantedTicks) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (-wantedTicks) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
		wait1Msec(40);
		waitUntil(AutoDriveBase.isCompleted);
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
