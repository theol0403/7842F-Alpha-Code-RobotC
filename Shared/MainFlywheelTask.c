

rpmStruct mainFlywheelRPM;
EMAFilter flywheelRPM_RA;


pidStruct mainFlywheelPID;
EMAFilter flywheelD_RA;



task FlywheelPIDTask()
{
	int slewRate = 1;

	rpmInit(mainFlywheelRPM, s_FlywheelEn, 360, 4.8);
	pidEMAInit(mainFlywheelPID, 0.55, 0.0, 6, 0.034, 1000, 100, 4000, flywheelD_RA, 0.04);

	filter_Init_EMA(flywheelRPM_RA, 0.09);

  int motorPower;
	int lastPower;
	int flywheelRPM;
  int filteredRPM;
  int motorTrue;

	while(true)
	{

		flywheelRPM = rpmCalculate(mainFlywheelRPM);
    filteredRPM = filter_EMA(flywheelRPM_RA, flywheelRPM);

    motorPower = pidEMACalculate(mainFlywheelPID, wantedFlywheelRPM, filteredRPM);


		if(motorPower < 0) motorPower = 0;

		if(motorPower > lastPower && lastPower < 20) lastPower = 20;

		if((motorPower - lastPower) > slewRate) motorPower = lastPower + slewRate;
    lastPower = motorPower;



    motorTrue = TrueSpeed(motorPower);

		setFlywheelPower(motorTrue);


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
