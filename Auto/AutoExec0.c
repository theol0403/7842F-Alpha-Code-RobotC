// Smurf Case 1



wantedFlywheelRPM = 2375;
AutoBaseDriveDistance(39.25);
AutoBaseWaitUntilDistance(33.1);
setIntakePower(127);
AutoBaseWaitUntilComplete();
AutoBaseDriveDistance(-29.3);


startTask(autoTurn);
wait(0.3);
SensorValue[Gyro] = 0;
target = -900;
pid = 1;
waitUntil(SensorValue[Gyro] < -880);
stopTask(intakeup);
motor[intake] = -127;
waitUntil(SensorValue[Ball] > linefollower);
wait(0.2);
startTask(intakeup);
SensorValue[Lquad] = 0;
SensorValue[Rquad] = 0;
Dtarget = 730;
RDtarget = 730;
pid = 2;
waitUntil(SensorValue[Lquad] > 720);
waitUntil(SensorValue[Rquad] > 720);
waitUntil(SensorValue[Ball] < linefollower);
stopTask(intakeup);
motor[intake] = -127;
waitUntil(SensorValue[Ball] > linefollower);
pid = 0;
SensorValue[Lquad] = 0;
SensorValue[Rquad] = 0;
Dtarget = 450;
RDtarget = 450;
pid = 2;
SensorValue[Gyro] = 0;
target = -160;
pid = 1;
waitUntil(SensorValue[Gyro] < -140);
SensorValue[Lquad] = 0;
SensorValue[Rquad] = 0;
RDtarget = 675;
Dtarget = 500;
pid = 2;
wait(0.3);
waitUntil(SensorValue[Rquad] > 475);
waitUntil(SensorValue[Lquad] > 400);
SensorValue[Lquad] = 0;
SensorValue[Rquad] = 0;
Dtarget = -1500;
RDtarget = -1500;
