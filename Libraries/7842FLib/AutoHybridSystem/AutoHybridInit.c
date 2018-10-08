


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

void AutoBaseInit_Config(int maxPower, int minPower, int completeThreshold, int completeTime)
{
	AutoDriveBase.maxPower = maxPower;
	AutoDriveBase.minPower = minPower;

	AutoDriveBase.completeThreshold = completeThreshold;
	AutoDriveBase.completeTime = completeTime;
	AutoDriveBase.taskLoopRate = 20;
}

void AutoBaseInit_PID(float Kp, float Ki, float Kd, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
	pidInit(AutoDriveLeftPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
	pidInit(AutoDriveRightPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
}
