




int joystickCh4;
int joystickCh2;
const int driverBaseThreshold = 20;

bool toggle = false;

task DriverMainTask()
{
	while(true)
	{

		// Base Control --------------------------------------------------------------------------------
		if(vexRT[Btn7U])
		{
			toggle = true;
		}
		else if(vexRT[Btn7D])
		{
			toggle = false;
		}

		if (toggle)
		{
			joystickCh4 = TrueSpeed(vexRT[Ch4]);
			joystickCh2 = TrueSpeed(vexRT[Ch2]);
		}
		else
		{
			joystickCh4 = vexRT[Ch4];
			joystickCh2 = vexRT[Ch2];
		}

		if(abs(joystickCh2) > driverBaseThreshold && !(abs(joystickCh4) > driverBaseThreshold) )
		{
			setBasePower(joystickCh2, joystickCh2);
		}
		else if(!(abs(joystickCh2) > driverBaseThreshold) && abs(joystickCh4) > driverBaseThreshold )
		{
			setBasePower(-joystickCh4, joystickCh4);
		}
		else if(abs(joystickCh2) > driverBaseThreshold && abs(joystickCh4) > driverBaseThreshold )
		{
			setBasePower(joystickCh2 - joystickCh4, joystickCh2 + joystickCh4);
		}
		else
		{
			setBasePower(0, 0);
		}
		// Base Control --------------------------------------------------------------------------------







		// Intake --------------------------------------------------------------------------------
		if(vexRT[Btn5U])
		{
			setIntakePower(127);
		}
		else if(vexRT[Btn5D])
		{
			setIntakePower(-127);
		}
		else
		{
			setIntakePower(0);
		}
		// Intake --------------------------------------------------------------------------------


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



		wait1Msec(20);
	}


}
