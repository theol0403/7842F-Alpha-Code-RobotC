
// struct odomStruct mainOdom;
// // OdomName, LeftSensor, RightSensor, ChassisDiameter, WheelDiameter, X, Y, Theta
// odomInit(mainOdom, s_LeftEn, s_RightEn, 18, 3, 0, 0, 0);
// odomSetPos(mainOdom, 5,6,5);
// odomGuessScales(mainOdom, 18, 3.8);
// while(true)
// {
//   odomCalculate(mainOdom);
//   y = odomGetY(mainOdom);
//   wait1Msec(5);
// }


struct odomStruct
{
  float distancePerTick;
  float chassisDiameter;
  tSensors leftQuad, rightQuad;

  float xPos;
  float yPos;
  float thetaPos;

  long leftSample, rightSample;
  long lastLeftSample, lastRightSample;

  float dLeftTicks, dRightTicks;
  float dLeftDistance, dRightDistance;
  float dAvgDistance;
};



void odomInit(odomStruct &odomName, tSensors leftQuad, tSensors rightQuad, float distancePerTick = 0, float chassisDiameter = 0, long startX = 0, long startY = 0, long startTheta = 0)
{
  odomName.distancePerTick = distancePerTick;
  odomName.chassisDiameter = chassisDiameter;

  odomName.leftQuad = leftQuad;
  odomName.rightQuad = rightQuad;

  odomName.xPos = startX;
  odomName.yPos = startY;
  odomName.thetaPos = startTheta;

  odomName.leftSample = 0;
  odomName.rightSample = 0;
  odomName.lastLeftSample = SensorValue[leftQuad];
  odomName.lastRightSample = SensorValue[rightQuad];

  odomName.dLeftTicks = 0;
  odomName.dRightTicks = 0;
  odomName.dLeftDistance = 0;
  odomName.dRightDistance = 0;
  odomName.dAvgDistance = 0;
}

void odomSetPos(odomStruct &odomName, long startX, long startY, long startTheta)
{
  odomName.xPos = startX;
  odomName.yPos = startY;
  odomName.thetaPos = startTheta;
}


void odomSetScale(odomStruct &odomName, float distancePerTick, float chassisDiameter)
{
  odomName.distancePerTick = distancePerTick;
  odomName.chassisDiameter = chassisDiameter;
}

void odomGuessScales(odomStruct &odomName, float chassisDiameter, float wheelDiameter)
{
  odomName.distancePerTick = wheelDiameter * PI / 360;
  odomName.chassisDiameter = chassisDiameter;
}

float odomGetX(odomStruct &odomName)
{
    return odomName.xPos;
}

float odomGetY(odomStruct &odomName)
{
    return odomName.yPos;
}

float odomGetDeg(odomStruct &odomName)
{
    return odomName.thetaPos;
}




void odomCalculate(odomStruct &odomName)
{
  //Save quads
  odomName.leftSample = SensorValue[odomName.leftQuad];
  odomName.rightSample = SensorValue[odomName.rightQuad];

  //Get delta
  odomName.dLeftTicks = odomName.leftSample - odomName.lastLeftSample;
  odomName.dRightTicks = odomName.rightSample - odomName.lastRightSample;

  //Save last vals
  odomName.lastLeftSample = odomName.leftSample;
  odomName.lastRightSample = odomName.rightSample;

  //Convert to distance
  odomName.dLeftDistance = odomName.dLeftTicks / odomName.distancePerTick;
  odomName.dRightDistance = odomName.dRightTicks / odomName.distancePerTick;

  //Get avg delta
  odomName.dAvgDistance = (odomName.dLeftDistance + odomName.dRightDistance) / 2;

  //Get theta
  odomName.thetaPos += (odomName.dLeftTicks - odomName.dRightTicks) / odomName.chassisDiameter;

  //Wrap theta
  if(odomName.thetaPos > 180) odomName.thetaPos -= 360;
  if(odomName.thetaPos <= -180) odomName.thetaPos += 360;


  //Do the odom math
  odomName.xPos += odomName.dAvgDistance * cosDegrees(odomName.thetaPos);
  odomName.yPos += odomName.dAvgDistance * sinDegrees(odomName.thetaPos);

}
