/* USE CASE
Somewhere, declare your RPM struct for a sensor/flywheel.
This will either be global or available to all your RPM calculate functions
* structRPM mainFlywheelRPM;
Somewhere, inside your code, so either in init, main, or some task,
run this function to Instantiate and populate your RPM struct.
The first param is your RPM struct name, The second is the sensor you are monitoring,
the third is the timer you are using to measure your RPM, the fourth is the ratio to your flywheel, so
it can output your flywheel RPM
* initRPM(mainFlywheelRPM, s_FlywheelEn, T2, 4.8);
Finally, to read the RPM, you can either read from:
* x = calculateRPM(mainFlywheelRPM);
Or you can have calculateRPM in a loop and read from
* x = mainFlywheelRPM.RPM;
Every 150 seconds it resets the timer and sensor to avoid overflowing the variables.
I have set the maximum refresh rate to 10ms.
Change both of these values in the InitRPM() function.
*/



//Structure containing RPM information for a sensor/flywheel pair
struct structRPM
{
	float timeInterval;
	float encoderInterval;

	float lastTime;
	float lastEncoder;

	int timerNum;
	float flywheelRatio;
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
 * @param flywheelRatio  ratio between rotation of sensor and rotation of flywheel
 *
 */
void initRPM(structRPM deviceName, int sensorNum, int timerNum, float flywheelRatio)
{
	deviceName.timeInterval = 0;
	deviceName.encoderInterval = 0;

	deviceName.lastTime = 0;
	deviceName.lastEncoder = 0;

	deviceName.timerNum = timerNum;
	deviceName.flywheelRatio = flywheelRatio;
	deviceName.sensorNum = sensorNum;
	deviceName.minRefresh = 10;
	deviceName.maxTimer = 10000;

	deviceName.RPM = 0;

	clearTimer(timerNum);
	SensorValue(sensorNum) = 0;
}

/**
 * Resets RPM values for a sensor / flywheel
 *
 * @param deviceName  instance of RPM structure
 *
 */
void resetRPM(structRPM deviceName)
{
	deviceName.timeInterval = 0;
	deviceName.encoderInterval = 0;

	deviceName.lastTime = 0;
	deviceName.lastEncoder = 0;

	clearTimer(deviceName.timerNum);
	SensorValue(deviceName.sensorNum) = 0;
}





/**
 * Calculate RPM calculation for a sensor / flywheel
 *
 * @param deviceName  instance of RPM structure
 *
 * @return  RPM of flywheel
 */
int calculateRPM(structRPM deviceName)
{
	//Calculate the amount of ms since the last time this function was run
	deviceName.timeInterval = time1[deviceName.timerNum] - deviceName.lastTime;
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
	deviceName.RPM = (60000 / deviceName.timeInterval) * (deviceName.encoderInterval/360) * deviceName.flywheelRatio;
	//rpm = 166.66 * encoderInterval / timeInterval;

	//If timer is greater than max timer size, reset everything
	if(time1[deviceName.timerNum] > deviceName.maxTimer) resetRPM(deviceName);

	//Timestamp the last time this function was run, and the encoder position
	deviceName.lastTime = time1[deviceName.timerNum];
	deviceName.lastEncoder = SensorValue(deviceName.sensorNum);

	//Return the RPM to whatever is calling this function
	return deviceName.RPM;

}
