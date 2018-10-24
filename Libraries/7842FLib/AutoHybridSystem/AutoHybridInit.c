
enum sideColors
{
  redSide,
  blueSide
};

enum baseModes
{
  baseDrive,
  baseTurn,
  baseAllign,
  //Insert new modes here

  baseModesNum
};


struct BaseStruct
{
	tSensors leftEn;
	tSensors rightEn;
	float wheelCircumference;
	float chassisCircumference;
  float emgDegTimeP;
  float emgInchTimeP;

//config
  int minPower[baseModesNum];
	int maxPower[baseModesNum];
	int completeThreshold[baseModesNum];
	int completeTime[baseModesNum];

	int loopRate;



	int wantedLeft;
	int wantedRight;
	bool brakeMode;

	int lastWantedLeft;
	int lastWantedRight;


	bool turnOn;
  baseModes baseMode;

	bool isCompleted;


  pidStruct autoBasePID[2][baseModesNum];
};


BaseStruct AutoDriveBase;




void AutoBaseInit_Chassis(tSensors leftEn, tSensors rightEn, float wheelCircumference, float chassisDiameter, float emgDegTimeP, float emgInchTimeP)
{
	AutoDriveBase.leftEn = leftEn;
	AutoDriveBase.rightEn = rightEn;
	AutoDriveBase.wheelCircumference = wheelCircumference;
	AutoDriveBase.chassisCircumference = chassisDiameter * 2 * 3.1415926;

	AutoDriveBase.wantedLeft = 0;
	AutoDriveBase.wantedRight = 0;
  SensorValue[AutoDriveBase.leftEn] = 0;
	SensorValue[AutoDriveBase.rightEn] = 0;


	AutoDriveBase.brakeMode = false;

	AutoDriveBase.turnOn = false;
	AutoDriveBase.isCompleted = false;

  AutoDriveBase.emgDegTimeP = emgDegTimeP;
  AutoDriveBase.emgInchTimeP = emgInchTimeP;

  AutoDriveBase.loopRate = 20;
}

void AutoBaseInit_Config(baseModes baseMode, int minPower, int maxPower, int completeThreshold, int completeTime, float Kp, float Ki, float Kd)
{
  AutoDriveBase.minPower[baseMode] = minPower;
	AutoDriveBase.maxPower[baseMode] = maxPower;

	AutoDriveBase.completeThreshold[baseMode] = completeThreshold;
	AutoDriveBase.completeTime[baseMode] = completeTime;

  pidInit(AutoDriveBase.autoBasePID[0][baseMode], Kp, Ki, Kd, 0, 100000, 0, 100000);
	pidInit(AutoDriveBase.autoBasePID[1][baseMode], Kp, Ki, Kd, 0, 100000, 0, 100000);

}
