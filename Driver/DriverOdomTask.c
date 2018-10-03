

struct odomStruct mainOdom;


// OdomName, LeftSensor, RightSensor, ChassisDiameter, WheelDiameter, X, Y, Theta
odomInit(mainOdom, s_LeftEn, s_RightEn, 18, 3, 0, 0, 0);
odomSetPos(mainOdom, 5,6,5);
odomGuessScales(mainOdom, 18, 3.8);
while(true)
{
  odomCalculate(mainOdom);
  y = odomGetY(mainOdom);
  wait1Msec(5);
}
