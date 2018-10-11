

void pidEMAInit (pidStruct &deviceName, float Kp, float Ki, float Kd, float Kf = 0, int Icap = 100000, int Iin = 0, int Iout = 100000, EMAFilter &raName, float emaAlpha)
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


	deviceName.raName = raName;
	filter_Init_EMA(deviceName.raName, emaAlpha);
}




float pidEMACalculate(pidStruct &deviceName, int wantedSig, int currentSig)
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
	if(deviceName.derivative < 0) deviceName.derivative /= 4;

	deviceName.derivative = filter_EMA(deviceName.raName, deviceName.derivative);

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
