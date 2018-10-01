

int slewRate = 2;

rpmStruct mainFlywheelRPM;
EMAFilter mainFlywheelRA;


pidStruct mainFlywheelPID;
EMAFilter mainFlywheelPIDRA;


task pidFlywheelTask()
{

	rpmInit(mainFlywheelRPM, s_FlywheelEn, 360, 4.8);
	pidRAInit(mainFlywheelPID, 0.10, 0.0, 4, 0.028, 1000, 100, 4000, &mainFlywheelPIDRA, 0.06);

	filter_Init_EMA(&mainFlywheelRA, 0.6);

  int motorPower;
	int lastPower;
	int flywheelRPM;
  int filteredRPM;
  int motorTrue;

	while(true)
	{

		flywheelRPM = rpmCalculate(mainFlywheelRPM);
    filteredRPM = filter_EMA(&mainFlywheelRA, flywheelRPM);

    motorPower = pidRACalculate(mainFlywheelPID, wantedFlywheelRPM, filteredRPM);


		if(motorPower < 0) motorPower = 0;

		if((motorPower - lastPower) > slewRate) motorPower = lastPower + slewRate;
    lastPower = motorPower;

    motorTrue = TrueSpeed(motorPower);

		setFlywheelPower(motorPower);


		datalogDataGroupStart();
 		datalogAddValue( 0, wantedFlywheelRPM /2);
 		datalogAddValue( 1,  flywheelRPM /2 );
    datalogAddValue( 2,  filteredRPM /2);
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
