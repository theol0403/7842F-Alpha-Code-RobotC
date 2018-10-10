// Smurf Case 1



wantedFlywheelRPM = 2000;

AutoBaseDriveDistance(39.25, false);
AutoBaseWaitUntilDistance(33.1);
AutoIntakeMode(intakeCollect);
AutoBaseWaitUntilComplete();
AutoIntakeMode(intakeOff);
AutoBaseDriveDistance(-29.3);
AutoBaseTurnDegrees(90);

AutoIntakeMode(intakeShoot);
wait1Msec(500);
AutoIntakeMode(intakeOff);

AutoBaseDriveDistance(25.47);
AutoIntakeMode(intakeShoot);
wait1Msec(500);
AutoIntakeMode(intakeOff);

AutoBaseDriveDistance(20);

AutoBaseDriveDistance(-53);
AutoBaseTurnDegrees(-90);
AutoBaseDriveDistance(-20);
