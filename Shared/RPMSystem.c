
/* USE CASE
Somewhere, declare your RPM struct for a sensor/flywheel.
This will either be global or available to all your RPM calculate functions
* rpmStruct rpmMainFlywheel;
Somewhere, inside your code, so either in init, main, or some task,
run the following function to Instantiate and populate your RPM struct.
* rpmIinit(rpmMainFlywheel, s_FlywheelEn, 360, 4.8);
The first param is your RPM struct name, The second is the sensor you are monitoring,
the third is the ticks of your sensor per rotation,
and forth is the ratio from your sensor to your flywheel, so it can output the flywheel RPM
Finally, to read the RPM, you can either read from:
* x = rpmCalculate(rpmMainFlywheel);
Or you can have rpmCalculate in a loop and read from
* x = rpmMainFlywheel.RPM;
*/

/* EXAMPLE
int globalFlywheelRPM;
rpmStruct rpmMainFlywheel;
task usercontrol()
{
  rpmInit(rpmMainFlywheel, s_FlywheelEn, 360, 4.8);
  while(true)
  {
    globalFlywheelRPM = rpmCalculate(rpmMainFlywheel);
    wait1Msec(20);
  }
}
*/



//Structure containing RPM information for a sensor/flywheel pair
struct rpmStruct
{
	float timeInterval;
	float encoderInterval;

	float lastTime;
	float lastEncoder;

	float flywheelRatio;
	float encoderTicks;
	int sensorNum;
	int minRefresh;
	int maxTimer;

	int RPM;
};


/**
 * Initialise RPM calculation for a sensor / flywheel
 *
 * @param deviceName  instance of RPM structure
 * @param sensorNum  enumerated value of sensor being read
 * @param timerNum  enumerated value of timer
 * @param encoderTicks  amount of ticks per rotation for your sensor - QuadEncoders are 360, IME are 4
 * @param flywheelRatio  ratio between sensor and flywheel
 *
 */
void rpmInit(rpmStruct &deviceName, int sensorNum, float encoderTicks, float flywheelRatio)
{
	deviceName.timeInterval = 0;
	deviceName.encoderInterval = 0;

	deviceName.lastTime = nPgmTime;
	deviceName.lastEncoder = 0;

	deviceName.flywheelRatio = flywheelRatio;
	deviceName.encoderTicks = encoderTicks;
	deviceName.sensorNum = sensorNum;
	deviceName.minRefresh = 10;

	deviceName.RPM = 0;

	SensorValue(sensorNum) = 0;
}




/**
 * Calculate RPM calculation for a sensor / flywheel
 *
 * @param deviceName  instance of RPM structure
 *S
 * @return  RPM of flywheel
 */
int rpmCalculate(rpmStruct &deviceName)
{
	//Calculate the amount of ms since the last time this function was run
	deviceName.timeInterval = nPgmTime - deviceName.lastTime;
	//Calculate amount of ticks since the function was last run
	deviceName.encoderInterval = SensorValue(deviceName.sensorNum) - deviceName.lastEncoder;

	//If it was ran very recently just return the last RPM
	if(deviceName.timeInterval < deviceName.minRefresh) return deviceName.RPM;

	//If either interval was 0, or sensor was 0, return 0
	if(deviceName.timeInterval == 0 || deviceName.encoderInterval == 0)
	{
		deviceName.RPM = 0;
		return 0;
	}

	//Calculate the RPM based off time and tick interval
	deviceName.RPM = (60000 / deviceName.timeInterval) * (deviceName.encoderInterval/deviceName.encoderTicks) * deviceName.flywheelRatio;


	//Timestamp the last time this function was run, and the encoder position
	deviceName.lastTime = nPgmTime;
	deviceName.lastEncoder = SensorValue(deviceName.sensorNum);

	//Return the RPM to whatever is calling this function
	return deviceName.RPM;

}
