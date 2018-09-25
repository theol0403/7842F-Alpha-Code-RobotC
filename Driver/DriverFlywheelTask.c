


struct PID
{
	float Kp;
	float Kd;
	float Ki;
	float Kf;
	int integralCap;
	int integralInner;
	int integralOuter;

	int Error;
  int totalError;
	int lastError;
	int lastTime;
	int lastIntegral;

  int wantedRPM;
  bool isTarget;
}


void pidInit (PID deviceName, float Kp, float Ki, float Kd, float Kf, int Icap, int Iin, int Iout)
{
	deviceName.Kp = Kp;
	deviceName.Ki = Ki;
	deviceName.Kd = Kd;
	deviceName.Kf = Kf;
	deviceName.integralCap = Icap;
  deviceName.integralInner = Iin;
	deviceName.integralOuter = Iout;

  deviceName.Error = 0;
	deviceName.lastError = 0;
  deviceName.totalError = 0;
	deviceName.lastTime = nPgmTime;
	deviceName.lastIntegral = 0;

  deviceName.isTarget = false;
}




float pidCalculate(PID deviceName, int wantedRPM, int currentRPM)
{
  deviceName.Error = wantedRPM - currentRPM;
	int deltaTime = nPgmTime - deviceName.lastTime;

  deviceName.totalError += (deviceName.Error * deltaTime);
  if(abs(deviceName.totalError) > deviceName.integralCap)
  {
    deviceName.totalError = sgn(deviceName.totalError) * deviceName.integralCap;
  }
  if(abs(deviceName.Error) < deviceName.integralInner) deviceName.totalError = deviceName.lastIntegral;
	if(abs(deviceName.Error) > deviceName.integralOuter) deviceName.totalError = deviceName.lastIntegral;


  float finalPower = (deviceName.Error * deviceName.Kp) + (deviceName.totalError * deviceName.Ki) + ((deviceName.Error - deviceName.lastError)*deviceName.Kd) + (wantedRPM * deviceName.Kf);

  deviceName.lastError = deviceName.Error;

	deviceName.lastTime = nPgmTime;
	deviceName.lastIntegral = deviceName.totalError;
  return finalPower;
}





PID pidFlywheel;
rpmStruct rpmMainFlywheel;



int wantedRPM = 0;

task pidFlywheeltask()
{
	int motorPower;
	int lastPower;
	pidInit(pidFlywheel, 0.15, 0.05, 0.00, 0.027, 1000, 100, 4000);
	rpmInit(rpmMainFlywheel, s_FlywheelEn, 4.8);
	while(true)
	{
		motorPower = pidCalculate(pidFlywheel, wantedRPM, rpmCalculate(rpmMainFlywheel));
		if(motorPower > 127) motorPower = 127;
		if(motorPower < 0) motorPower = 0;
		//if((motorPower - lastPower) > 3) motorPower = 3;
		setFlywheelPower(motorPower);
		lastPower = motorPower;
		wait1Msec(20);
	}
}









/*


bool flywheelToggle = false;

//max speed = 750;

task flywheelTask()
{

	while(true)
	{

		if(vexRT[Btn6U])
		{
			flywheelToggle = true
		}
		else if(vexRT[Btn6D])
		{
			flywheelToggle = false;
		}


		if(flywheelToggle)
		{
			setFlywheelPower
		}

		for(int i = 40; i < 127; i++)
		{
			setFlywheelPower(i);
			delay(60);
		}
		delay(1000000);
	}
}

task flywheelTask()
{
	for(int i = 40; i < 127; i++)
		{
			setFlywheelPower(i);
			delay(60);
		}
		delay(1000000);
}


// Flywheel BangBang --------------------------------------------------------------------------------
if(vexRT[Btn6U])
{
	startTask(flywheelTask);
}
else if(vexRT[Btn6D])
{
	stopTask(flywheelTask);
	setFlywheelPower(0);
}
// Flywheel BangBang --------------------------------------------------------------------------------






task DriverFlywheelTask()
{

while(true)
{

}
}


// Flywheel BangBang --------------------------------------------------------------------------------
if(vexRT[Btn6U])
{
startTask(flywheelTask);
}
else if(vexRT[Btn6D])
{
stopTask(flywheelTask);
setFlywheelPower(0);
}
// Flywheel BangBang --------------------------------------------------------------------------------
*/
