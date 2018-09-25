
int joystickCh4;
int joystickCh2;
const int driverBaseThreshold = 20;


task DriverMainTask()
{


	while(true)
	{

		// Base Control --------------------------------------------------------------------------------


			joystickCh4 = TrueSpeed(vexRT[Ch4]);
			joystickCh2 = TrueSpeed(vexRT[Ch2]);


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


		if(vexRT[Btn7D])
		{
			wantedFLywheelRPM = 0;
		}
		else if(vexRT[Btn7L])
		{
			wantedFLywheelRPM = 1000;
		}
		else if(vexRT[Btn7U])
		{
			wantedFLywheelRPM = 2000;
		}
		else if(vexRT[Btn7R])
		{
			wantedFLywheelRPM = 3000;
		}



		wait1Msec(20);
	}

}
