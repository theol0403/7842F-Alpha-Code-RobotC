
enum sideColors
{
  redSide = 1,
  blueSide = -1
};


struct BaseStruct
{
	tSensors leftEn;
	tSensors rightEn;
	float wheelCircumference;
	float chassisCircumference;
	sideColors chosenSide;

  int minPower;
	int maxPower;
	int completeThreshold;
	int completeTime;
	int loopRate;

  float emgDegTimeP;
  float emgInchTimeP;

	int wantedLeft;
	int wantedRight;
	bool brakeMode;

	int lastWantedLeft;
	int lastWantedRight;



	bool turnOn;
	bool isCompleted;
};



BaseStruct AutoDriveBase;
pidStruct AutoDriveLeftPID;
pidStruct AutoDriveRightPID;


void AutoBaseInit_Chassis(tSensors leftEn, tSensors rightEn, float wheelCircumference, float chassisDiameter, sideColors chosenSide)
{
	AutoDriveBase.leftEn = leftEn;
	AutoDriveBase.rightEn = rightEn;
	AutoDriveBase.wheelCircumference = wheelCircumference;
	AutoDriveBase.chassisCircumference = chassisDiameter * 2 * 3.1415926;
	AutoDriveBase.chosenSide = chosenSide;

	AutoDriveBase.wantedLeft = SensorValue[leftEn];
	AutoDriveBase.wantedRight = SensorValue[rightEn];
	AutoDriveBase.brakeMode = false;

	AutoDriveBase.turnOn = false;
	AutoDriveBase.isCompleted = false;
}

void AutoBaseInit_Config(int minPower, int maxPower, int completeThreshold, int completeTime, float emgDegTimeP, float emgInchTimeP)
{
  AutoDriveBase.minPower = minPower;
	AutoDriveBase.maxPower = maxPower;

	AutoDriveBase.completeThreshold = completeThreshold;
	AutoDriveBase.completeTime = completeTime;
	AutoDriveBase.loopRate = 20;

  AutoDriveBase.emgDegTimeP = emgDegTimeP;
  AutoDriveBase.emgInchTimeP = emgInchTimeP;
}

void AutoBaseInit_PID(float Kp, float Ki, float Kd, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
	pidInit(AutoDriveLeftPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
	pidInit(AutoDriveRightPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
}
