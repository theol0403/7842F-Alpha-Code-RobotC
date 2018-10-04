

struct odomStruct mainOdom;
task DriverOdomTask()
{
  // OdomName, LeftSensor, RightSensor, ChassisDiameter, WheelDiameter, X, Y, Theta
  odomInit(mainOdom, s_LeftEn, s_RightEn);
  odomGuessScales(mainOdom, 5.03, 12.57);
  //odomSetPos(mainOdom, 5,6,5);


  while(true)
  {
    odomCalculate(mainOdom);
    wait1Msec(1);
  }
}

bool honeTheta = true;
int wantOdom = 0;

int limit = 30;
task odomTest()
{
  int error;
  int p;
  int kp = 6;
  int left;
  int right;
  while(true)
  {
    if(honeTheta)
    {
      error = wantOdom - odomGetDeg(mainOdom);
      p = error*kp;
      if(abs(p) > 20) p = 20 * sgn(p);
      setBasePower(-p, p);
    }
    else
    {
      joystickCh4 = abs(vexRT[Ch4]) < driverBaseThreshold ? 0 : vexRT[Ch4];
      joystickCh2 = abs(vexRT[Ch2]) < driverBaseThreshold ? 0 : vexRT[Ch2];
      trueJoystickCh4 = TrueSpeed(joystickCh4);
      trueJoystickCh2 = TrueSpeed(joystickCh2);

left = trueJoystickCh2 - trueJoystickCh4;
right = trueJoystickCh2 + trueJoystickCh4;
if(abs(left) > 25) left = 25 * sgn(left);
if(abs(right) > 25) right = 25 * sgn(right);
        setBasePower(left, right);

    }

    if(vexRT[Btn8D] && honeTheta)
    {
      honeTheta = false;
      waitUntil(!vexRT[Btn8D]);
    }
    else if(vexRT[Btn8D] && !honeTheta)
    {
      honeTheta = true;
      waitUntil(!vexRT[Btn8D]);
    }
    wait1Msec(20);
  }
}
