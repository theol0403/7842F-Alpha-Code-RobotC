


#ifndef __7842F_PID_SYSTEM_H
#define __7842F_PID_SYSTEM_H

struct pidStruct
{
	float Kp;
	float Kd;
	float Ki;
	float Kf;
	int integralCap;
	int integralInner;
	int integralOuter;

	int Error;
  int totalError;
	int lastError;
	int lastTime;
	int lastIntegral;
  float derivative;

  int wantedRPM;
  bool isTarget;

  EMAFilter *raName;
};


#endif
