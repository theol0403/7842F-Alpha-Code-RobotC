

int slewRate = 1;

rpmStruct mainFlywheelRPM;
EMAFilter mainFlywheelRPM_RA;


pidStruct mainFlywheelPID;
EMAFilter mainFlywheelPID_RA;


task pidFlywheelTask()
{

	rpmInit(mainFlywheelRPM, s_FlywheelEn, 360, 4.8);
	pidRAInit(mainFlywheelPID, 0.10, 0.0, 4, 0.028, 1000, 100, 4000, &mainFlywheelPID_RA, 0.06);

	filter_Init_EMA(&mainFlywheelRPM_RA, 0.6);

  int motorPower;
	int lastPower;
	int flywheelRPM;
  int filteredRPM;
  int motorTrue;

	while(true)
	{

		flywheelRPM = rpmCalculate(mainFlywheelRPM);
    filteredRPM = filter_EMA(&mainFlywheelRPM_RA, flywheelRPM);

    motorPower = pidRACalculate(mainFlywheelPID, wantedFlywheelRPM, filteredRPM);


		if(motorPower < 0) motorPower = 0;

		if((motorPower - lastPower) > slewRate) motorPower = lastPower + slewRate;
    lastPower = motorPower;

    motorTrue = TrueSpeed(motorPower);

		setFlywheelPower(motorPower);


		datalogDataGroupStart();
 		datalogAddValue( 0, wantedFlywheelRPM /4);
 		datalogAddValue( 1,  flywheelRPM /4 );
    datalogAddValue( 2,  filteredRPM /4);
    datalogAddValue( 3, motorPower );
    datalogAddValue( 4, motorTrue );

    datalogAddValue( 5, mainFlywheelPID.derivative );
 		datalogDataGroupEnd();

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
