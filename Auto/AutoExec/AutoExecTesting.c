
AutoBaseDriveDistance(30);
AutoBaseDriveDistance(-30);

wait1Msec(2000);

AutoBaseDriveDistance(30, true, false);
AutoBaseDriveDistance(-30, true, false);

wait1Msec(2000);

AutoBaseDriveDistance(30, false);
AutoBaseWaitUntilDistance(10);
//Yeet
AutoBaseWaitUntilComplete();
AutoBaseDriveDistance(-30, false);
wait1Msec(2000);



AutoBaseTurnDegrees(90);
AutoBaseTurnDegrees(-90);

wait1Msec(2000);

AutoBaseTurnDegrees(90, true, false);
AutoBaseTurnDegrees(-90, true, false);

wait1Msec(2000);

AutoBaseTurnDegrees(90, false);
AutoBaseWaitUntilDegrees(45);
//Yeet
AutoBaseWaitUntilComplete();
AutoBaseTurnDegrees(-90, false);
wait1Msec(2000);
