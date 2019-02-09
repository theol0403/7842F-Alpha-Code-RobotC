
enum sideColors
{
  redSide = 1,
  blueSide = -1
};

enum baseModes
{
  baseDrive = 0,
  baseTurn = 1,
  baseAllign = 2,
  baseDriveSlow = 3
};


struct BaseStruct
{
  tSensors leftEn;
  tSensors rightEn;
  float wheelCircumference;
  float chassisCircumference;
  float emgDegTimeP;
  float emgInchTimeP;
  sideColors chosenSide;

  //config
  int minPower[4];
  int maxPower[4];
  int completeThreshold[4];
  int completeTime[4];

  int loopRate;



  int wantedLeft;
  int wantedRight;
  bool brakeMode;

  int lastWantedLeft;
  int lastWantedRight;


  bool turnOn;
  baseModes baseMode;

  bool isCompleted;
};



BaseStruct AutoDriveBase;
pidStruct AutoDriveLeftPID;
pidStruct AutoDriveRightPID;


void AutoBaseInit_Chassis(tSensors leftEn, tSensors rightEn, float wheelCircumference, float chassisDiameter, float emgDegTimeP, float emgInchTimeP, sideColors chosenSide)
{
  AutoDriveBase.leftEn = leftEn;
  AutoDriveBase.rightEn = rightEn;
  AutoDriveBase.wheelCircumference = wheelCircumference;
  AutoDriveBase.chassisCircumference = chassisDiameter * 2 * 3.1415926;
  AutoDriveBase.chosenSide = chosenSide;

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

void AutoBaseInit_Config(baseModes baseMode, int minPower, int maxPower, int completeThreshold, int completeTime)
{
  AutoDriveBase.minPower[baseMode] = minPower;
  AutoDriveBase.maxPower[baseMode] = maxPower;

  AutoDriveBase.completeThreshold[baseMode] = completeThreshold;
  AutoDriveBase.completeTime[baseMode] = completeTime;

}



void AutoBaseInit_PID(float Kp, float Ki, float Kd, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
  pidInit(AutoDriveLeftPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
  pidInit(AutoDriveRightPID, Kp, Ki, Kd, 0, Icap, Iin, Iout);
}
