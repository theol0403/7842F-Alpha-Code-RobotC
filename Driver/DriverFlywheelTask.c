
task flywheelTask()
{
	for(int i = 40; i < 127; i++)
	{
		setFlywheelPower(i);
		delay(60);
	}
	delay(1000000);
}






/*

PID flywheelPID;


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
