
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

wantedFlywheelRPM = 2700;
AutoIntakeMode(intakeCollect);

AutoBaseDriveDistance(-38);
AutoBaseDriveDistance(42);
AutoBaseDriveAllign(30, 800);
AutoBaseDriveDistance(-33);


AutoBaseTurnDegrees(-91);

AutoBaseDriveDistance(-12, true, false);
wait1Msec(2500);
AutoIntakeMode(indexShoot);
wait1Msec(300);
AutoIntakeMode(intakeCollect);


AutoBaseDriveDistance(38, false);
AutoBaseWaitUntilDistance(28);
AutoIntakeMode(indexShoot);
AutoBaseWaitUntilComplete();
AutoIntakeMode(intakeCollect);

AutoBaseTurnDegrees(19);
AutoBaseDriveAllign(18, 2000);

AutoBaseDriveDistance(-25);
AutoBaseTurnDegrees(90);
AutoIntakeMode(intakeOut);
AutoBaseDriveDistance(-20);




wantedFlywheelRPM = 0;
AutoIntakeMode(intakeOff);
AutoBaseDriveDistance(0, false, false);
