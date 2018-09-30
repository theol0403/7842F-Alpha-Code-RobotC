
int joystickCh4;
int joystickCh2;
int trueJoystickCh4;
int trueJoystickCh2;
const int driverBaseThreshold = 20;


task DriverMainTask()
{


	while(true)
	{

		// Base Control --------------------------------------------------------------------------------


			joystickCh4 = vexRT[Ch4];
			joystickCh2 = vexRT[Ch2];
			trueJoystickCh4 = TrueSpeed(joystickCh4);
			trueJoystickCh2 = TrueSpeed(joystickCh2);


		if(abs(joystickCh2) > driverBaseThreshold && !(abs(joystickCh4) > driverBaseThreshold) )
		{
			setBasePower(trueJoystickCh2, trueJoystickCh2);
		}
		else if(!(abs(joystickCh2) > driverBaseThreshold) && abs(joystickCh4) > driverBaseThreshold )
		{
			setBasePower(-trueJoystickCh4, trueJoystickCh4);
		}
		else if(abs(joystickCh2) > driverBaseThreshold && abs(joystickCh4) > driverBaseThreshold )
		{
			setBasePower(trueJoystickCh2 - trueJoystickCh4, trueJoystickCh2 + trueJoystickCh4);
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
			wantedFlywheelRPM = 0;
		}
		else if(vexRT[Btn7L])
		{
			wantedFlywheelRPM = 1000;
		}
		else if(vexRT[Btn7U])
		{
			wantedFlywheelRPM = 2000;
		}
		else if(vexRT[Btn7R])
		{
			wantedFlywheelRPM = 3000;
		}



		wait1Msec(20);
	}

}
