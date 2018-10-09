


void AutoBaseDriveDistance(int wantedLeftInch, int wantedRightInch, bool blockMode = true, bool brakeMode = true)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	AutoDriveBase.wantedLeft += (wantedLeftInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.wantedRight += (wantedRightInch / AutoDriveBase.wheelCircumference) * 360;
	AutoDriveBase.brakeMode = brakeMode;

	if(blockMode)
	{
    int emergencyCount = 0;
    int longestStep = abs(wantedLeftInch) > abs(wantedRightInch) ? abs(wantedLeftInch) : abs(wantedRightInch);

		wait1Msec(AutoDriveBase.loopRate * 2);
    while(!AutoDriveBase.isCompleted && emergencyCount < AutoDriveBase.emgInchTimeP * longestStep)
    {
      emergencyCount += AutoDriveBase.loopRate;
      wait1Msec(AutoDriveBase.loopRate);
    }
	}

}

void AutoBaseTurnDegrees(int wantedDegrees, bool blockMode = true, bool brakeMode = true, int forwardBiasInch = 0)
{
	AutoDriveBase.turnOn = true;
	AutoDriveBase.isCompleted = false;
	int wantedTicks = AutoDriveBase.chassisCircumference / AutoDriveBase.wheelCircumference * wantedDegrees;
	AutoDriveBase.wantedLeft += (wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.wantedRight += (-wantedTicks/2) + (forwardBiasInch / AutoDriveBase.wheelCircumference * 360);
	AutoDriveBase.brakeMode = brakeMode;

  if(blockMode)
	{
    int emergencyCount = 0;
		wait1Msec(AutoDriveBase.loopRate * 2);
    while(!AutoDriveBase.isCompleted && emergencyCount < AutoDriveBase.emgDegTimeP * abs(wantedDegrees))
    {
      emergencyCount += AutoDriveBase.loopRate;
      wait1Msec(AutoDriveBase.loopRate);
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
