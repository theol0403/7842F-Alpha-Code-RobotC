


void pidInit (pidStruct &deviceName, float Kp, float Ki, float Kd, float Kf = 0, int Icap = 100000, int Iin = 0, int Iout = 100000)
{
	deviceName.Kp = Kp;
	deviceName.Ki = Ki;
	deviceName.Kd = Kd;
	deviceName.Kf = Kf;

	deviceName.integralCap = Icap;
  deviceName.integralInner = Iin;
	deviceName.integralOuter = Iout;

  deviceName.Error = 0;
	deviceName.lastError = 0;
  deviceName.totalError = 0;
	deviceName.lastTime = nPgmTime;
	deviceName.lastIntegral = 0;
	deviceName.derivative = 0;

}





float pidCalculate(pidStruct &deviceName, int wantedSig, int currentSig)
{
  deviceName.Error = wantedSig - currentSig;
	int deltaTime = nPgmTime - deviceName.lastTime;

  deviceName.totalError += (deviceName.Error * deltaTime);
  if(abs(deviceName.totalError) > deviceName.integralCap)
  {
    deviceName.totalError = sgn(deviceName.totalError) * deviceName.integralCap;
  }
  if(abs(deviceName.Error) < deviceName.integralInner) deviceName.totalError = deviceName.lastIntegral;
	if(abs(deviceName.Error) > deviceName.integralOuter) deviceName.totalError = deviceName.lastIntegral;

	deviceName.derivative = deviceName.Error - deviceName.lastError;

  float finalPower = (deviceName.Error * deviceName.Kp) + (deviceName.totalError * deviceName.Ki) + (deviceName.derivative * deviceName.Kd) + (wantedSig * deviceName.Kf);

  deviceName.lastError = deviceName.Error;

	deviceName.lastTime = nPgmTime;
	deviceName.lastIntegral = deviceName.totalError;

	if(abs(finalPower) > 127)
	{
		finalPower = sgn(finalPower) * 127;
	}

  return finalPower;
}











// /**
//  * PID controller data structure
//  */
// typedef struct {
// 	float Kp;
// 	float Ki;
// 	float Kd;
// 	float Kf;
// 	float sigma;
// 	float lastValue;
// 	unsigned long lastTime;
// 	float lastSetPoint;
// } PID;
//
//
//
//
// /**
//  * initialize pid structure, set parameters
//  *
//  * pid instance of PID structure
//  * Kp  proportional gain
//  * Ki  integral gain
//  * Kd  derivative gain
//  * innerIntegralBand  inner bound of PID I summing cutoff
//  * outerIntegralBand  outer bound of PID I summing cutoff
//  */
// void
// pidInit (PID pid, float Kp, float Ki, float Kd) {
// 	pid.Kp = Kp;
// 	pid.Ki = Ki;
// 	pid.Kd = Kd;
// 	pid.Kf = 0.0;
// 	pid.sigma = 0;
// 	pid.lastValue = 0;
// 	pid.lastTime = nPgmTime;
// }
//
// void pidInit (PID pid, float Kp, float Ki, float Kd, float Kf) {
// 	pid.Kp = Kp;
// 	pid.Ki = Ki;
// 	pid.Kd = Kd;
// 	pid.Kf = Kf;
// 	pid.sigma = 0;
// 	pid.lastValue = 0;
// 	pid.lastTime = nPgmTime;
// }
//
// /**
//  * initialize pid structure, set parameters based on another PID structure
//  *
//  * @param pid  instance of PID structure
//  * @param toCopy  PID instance to copy settings from
//  */
// void pidInitCopy (PID pid, PID toCopy) {
// 	pid.Kp = toCopy.Ki;
// 	pid.Ki = toCopy.Ki;
// 	pid.Kd = toCopy.Kd;
// 	pid.Kf = toCopy.Kf;
// 	pid.sigma = 0;
// 	pid.lastValue = 0;
// 	pid.lastTime = nPgmTime;
// }
//
// /**
//  * calculate pid output
//  *
//  * @param pid  instance of PID structure
//  * @param setPoint  set point of PID controller
//  * @param processVariable  sensor/feedback value
//  *
//  * @return  output value of the control loop
//  */
// float
// pidCalculate (PID pid, float setPoint, float processVariable) {
// 	float deltaTime = (nPgmTime - pid.lastTime)*0.001;
// 	pid.lastTime = nPgmTime;
//
// 	float deltaPV = 0;
//
//   if(deltaTime > 0) {
// 		deltaPV = (processVariable - pid.lastValue) / deltaTime;
//   }
//
//   pid.lastValue = processVariable;
//
// 	float error = setPoint - processVariable;
//
//   float output = error * pid.Kp + pid.sigma * pid.Ki - deltaPV * pid.Kd + setPoint * pid.Kf;
//
// 	if (!(fabs(output) >= 1.0 && ((error >= 0 && pid.sigma >= 0) || (error < 0 && pid.sigma < 0)))) {
//     pid.sigma += error * deltaTime;
//   }
//
// 	output = error * pid.Kp
// 					+ pid.sigma * pid.Ki
// 					- deltaPV * pid.Kd
// 					+ setPoint * pid.Kf;
//
//   if (output > 1.0) {
//     output = 1.0;
//   }
//
//   if (output < -1.0) {
//     output = -1.0;
//   }
//
// 	return output;
// }
