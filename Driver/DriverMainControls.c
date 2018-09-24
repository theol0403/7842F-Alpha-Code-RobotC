



structRPM mainFlywheelRPM;


int flywheelRPM;


int joystickCh4;
int joystickCh2;
const int driverBaseThreshold = 20;


task DriverMainTask()
{
	 initRPM(mainFlywheelRPM, s_FlywheelEn, T2, 4.8);



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




		flywheelRPM = calculateRPM(mainFlywheelRPM);



		wait1Msec(20);
	}


}
