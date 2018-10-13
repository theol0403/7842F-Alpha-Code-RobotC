
//flywheel bit less than middle rpm - 2500
//-38 inch w/ intake
//38
//turn -90
//-26
//Shoot

//68
//-23
//turn 90
//outtake
//-24

wantedFlywheelRPM = 2500;
AutoIntakeMode(intakeCollect);

AutoBaseDriveDistance(-38);
wait1Msec(200);
AutoBaseDriveDistance(42);
AutoBaseDriveAllign(30, 800);
AutoBaseDriveDistance(-6);


AutoBaseTurnDegrees(91);

AutoBaseDriveDistance(-11, true, false);

waitUntil(mainFlywheelPID.Error < 30);
wait1Msec(300);
AutoIntakeMode(indexShoot);
wait1Msec(300);
AutoIntakeMode(intakeCollect);



AutoBaseDriveDistance(38, false);
AutoBaseWaitUntilDistance(24);
AutoIntakeMode(indexShoot);
AutoBaseWaitUntilComplete();
AutoIntakeMode(intakeCollect);


AutoBaseTurnDegrees(-18);
AutoBaseDriveDistance(8);
AutoBaseTurnDegrees(18);
AutoBaseDriveAllign(26, 1000);

AutoBaseDriveDistance(-20);
AutoBaseTurnDegrees(-90);
AutoIntakeMode(intakeOut);
AutoBaseDriveDistance(-24);




wantedFlywheelRPM = 0;
AutoIntakeMode(intakeOff);
AutoBaseDriveDistance(0, false, false);
