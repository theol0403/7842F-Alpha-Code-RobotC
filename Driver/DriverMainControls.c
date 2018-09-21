task flywheelTask()
{
	for(int i = 40; i < 127; i++)
	{
		setFlywheelPower(i);
		delay(60);
	}
	delay(1000000);
}






int joystickCh4;
int joystickCh2;
const int driverBaseThreshold = 20;


task DriverMainTask()
{
	while(true)
	{

// Base Control --------------------------------------------------------------------------------
joystickCh4 = vexRT[Ch4];
joystickCh2 = vexRT[Ch2];
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






wait1Msec(20);
  }


}
