


struct PID
{
	float Kp;
	float Kd;
	float Ki;
	int integralCap;

	int Error;
  int totalError;
	int lastError;
	int lastTime;

  int wantedRPM;
  bool isTarget;
}


void pidInit (PID deviceName, float Kp, float Ki, float Kd, int Icap, int Idead)
{
	deviceName.Kp = Kp;
	deviceName.Ki = Ki;
	deviceName.Kd = Kd;
	deviceName.integralCap = Icap;
  deviceName.integralDeadzone = Idead;

  deviceName.Error = 0;
	deviceName.lastError = 0;
  deviceName.totalError = 0;
	deviceName.lastTime = nPgmTime;

  deviceName.isTarget = false;
}




float pidCalculate(PID deviceName, int wantedRPM, int currentRPM)
{
  deviceName.Error = wantedRPM - currentRPM;

  deviceName.totalError += Error;
  if(abs(deviceName.totalError) > deviceName.integralCap)
  {
    deviceName.totalError = sgn(deviceName.totalError) * deviceName.integralCap;
  }
  if(abs(deviceName.Error) < deviceName.integralDeadzone) deviceName.totalError = 0;


  float finalPower = (deviceName.Error * deviceName.Kp) +

  deviceName.lastError = deviceName.Error;

  return finalPower
}





PID pidFlywheel;

task pidFlywheeltask()
{
	initPID(pidFlywheel, 1, 0, 0, 1000, 10);
	while(true)
	{
		motor += pidCalculate
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
