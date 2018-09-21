



void setFlywheelPower(int flywheelSpeed)
{
	motor[m_Flywheel] = flywheelSpeed;
	motor[m_Flywheel2] = flywheelSpeed;
}

void setIntakePower(int intakeSpeed)
{
	motor[m_Intake] = intakeSpeed;
}

void setBasePower(int rightSpeed, int leftSpeed)
{
	motor[m_RightBase] = rightSpeed;
	motor[m_LeftBase] = leftSpeed;
	motor[m_RightBase2] = rightSpeed;
	motor[m_LeftBase2] = leftSpeed;
}








/**
 * PID controller data structure
 */
typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float Kf;
	float sigma;
	float lastValue;
	unsigned long lastTime;
	float lastSetPoint;
} PID;




/**
 * initialize pid structure, set parameters
 *
 * pid instance of PID structure
 * Kp  proportional gain
 * Ki  integral gain
 * Kd  derivative gain
 * innerIntegralBand  inner bound of PID I summing cutoff
 * outerIntegralBand  outer bound of PID I summing cutoff
 */
void
pidInit (PID pid, float Kp, float Ki, float Kd) {
	pid.Kp = Kp;
	pid.Ki = Ki;
	pid.Kd = Kd;
	pid.Kf = 0.0;
	pid.sigma = 0;
	pid.lastValue = 0;
	pid.lastTime = nPgmTime;
}

void pidInit (PID pid, float Kp, float Ki, float Kd, float Kf) {
	pid.Kp = Kp;
	pid.Ki = Ki;
	pid.Kd = Kd;
	pid.Kf = Kf;
	pid.sigma = 0;
	pid.lastValue = 0;
	pid.lastTime = nPgmTime;
}

/**
 * initialize pid structure, set parameters based on another PID structure
 *
 * @param pid  instance of PID structure
 * @param toCopy  PID instance to copy settings from
 */
void pidInitCopy (PID pid, PID toCopy) {
	pid.Kp = toCopy.Ki;
	pid.Ki = toCopy.Ki;
	pid.Kd = toCopy.Kd;
	pid.Kf = toCopy.Kf;
	pid.sigma = 0;
	pid.lastValue = 0;
	pid.lastTime = nPgmTime;
}

/**
 * calculate pid output
 *
 * @param pid  instance of PID structure
 * @param setPoint  set point of PID controller
 * @param processVariable  sensor/feedback value
 *
 * @return  output value of the control loop
 */
float
pidCalculate (PID pid, float setPoint, float processVariable) {
	float deltaTime = (nPgmTime - pid.lastTime)*0.001;
	pid.lastTime = nPgmTime;

	float deltaPV = 0;

  if(deltaTime > 0) {
		deltaPV = (processVariable - pid.lastValue) / deltaTime;
  }

  pid.lastValue = processVariable;

	float error = setPoint - processVariable;

  float output = error * pid.Kp + pid.sigma * pid.Ki - deltaPV * pid.Kd + setPoint * pid.Kf;

	if (!(fabs(output) >= 1.0 && ((error >= 0 && pid.sigma >= 0) || (error < 0 && pid.sigma < 0)))) {
    pid.sigma += error * deltaTime;
  }

	output = error * pid.Kp
					+ pid.sigma * pid.Ki
					- deltaPV * pid.Kd
					+ setPoint * pid.Kf;

  if (output > 1.0) {
    output = 1.0;
  }

  if (output < -1.0) {
    output = -1.0;
  }

	return output;
}



// compensates for non-linearity of control value vs speed curve
const unsigned int trueSpeedArray[129] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127,127
};

int TrueSpeed(int value)
{
	return sgn(vexRT[value]) * trueSpeedArray[abs(vexRT[value])];
}
