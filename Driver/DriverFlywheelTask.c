








PID pidFlywheel;
rpmStruct rpmMainFlywheel;





task pidFlywheeltask()
{
	int motorPower;
	int lastPower;
	rpmInit(rpmMainFlywheel, s_FlywheelEn, 360, 4.8);
	pidInit(pidFlywheel, 0.10, 0.0, 0.01, 0.028, 1000, 100, 4000);
	while(true)
	{
		motorPower = pidCalculate(pidFlywheel, wantedRPM, rpmCalculate(rpmMainFlywheel));
		if(motorPower < 0) motorPower = 0;
		if((motorPower - lastPower) > 5) motorPower = lastPower + 5;
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
