
int joystickCh4;
int joystickCh2;
int trueJoystickCh4;
int trueJoystickCh2;
const int driverBaseThreshold = 25;

bool flywheelManual = false;


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
			setBasePower(trueJoystickCh4, -trueJoystickCh4);
		}
		else if(abs(joystickCh2) > driverBaseThreshold && abs(joystickCh4) > driverBaseThreshold )
		{
			setBasePower(trueJoystickCh2 + trueJoystickCh4, trueJoystickCh2 - trueJoystickCh4);
		}
		else
		{
			setBasePower(0, 0);
		}
		// Base Control --------------------------------------------------------------------------------




		// Intake --------------------------------------------------------------------------------
		if(vexRT[Btn6U])
		{
			setIntakePower(127);
			setIndexerPower(127);
		}
		else if(vexRT[Btn6D])
		{
			setIntakePower(-127);
			setIndexerPower(-15);
		}
		else
		{
			setIntakePower(0);
			setIndexerPower(0);
		}

		if(vexRT[Btn5D])
		{
			setIndexerPower(-127);
		}
		else if(vexRT[Btn5U])
		{
			setIndexerPower(127);
		}

		// Intake --------------------------------------------------------------------------------

		// Index --------------------------------------------------------------------------------


		// Index --------------------------------------------------------------------------------

		if(flywheelManual)
		{
			if(vexRT[Btn7D])
			{
				setFlywheelPower(0);
			}
			else if(vexRT[Btn7L])
			{
				setFlywheelPower(70);
			}
			else if(vexRT[Btn7U])
			{
				setFlywheelPower(90);
			}
			else if(vexRT[Btn7R])
			{
				setFlywheelPower(110);
			}
		}
		else
		{
			if(vexRT[Btn7D])
			{
				wantedFlywheelRPM = 0;
			}
			else if(vexRT[Btn7L])
			{
				wantedFlywheelRPM = 2300;
			}
			else if(vexRT[Btn7U])
			{
				wantedFlywheelRPM = 2500;
			}
			else if(vexRT[Btn7R])
			{
				wantedFlywheelRPM = 2800;
			}
		}




		if(vexRT[Btn8U] && !flywheelManual)
		{
			stopTask(FlywheelPIDTask);
			flywheelManual = true;
		}
		else if(vexRT[Btn8L] && flywheelManual)
		{
			startTask(FlywheelPIDTask);
			flywheelManual = false;
		}



		wait1Msec(20);
	}

}
