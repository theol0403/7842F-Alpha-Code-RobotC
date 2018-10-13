
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
AutoBaseDriveDistance(-8);


AutoBaseTurnDegrees(-90);

AutoBaseDriveDistance(-10, true, false);

waitUntil(mainFlywheelPID.Error < 30);
wait1Msec(300);
AutoIntakeMode(indexShoot); //sho
wait1Msec(300);
AutoIntakeMode(intakeCollect);



AutoBaseDriveDistance(33);
AutoIntakeMode(indexShoot);
wait1Msec(300);
AutoBaseDriveDistance(5);
AutoIntakeMode(intakeCollect);


AutoBaseTurnDegrees(19);
AutoBaseDriveDistance(9);
AutoBaseTurnDegrees(-19);
AutoBaseDriveAllign(26, 1000);

AutoBaseDriveDistance(-20);
AutoBaseTurnDegrees(90);

AutoIntakeMode(intakeOut);
AutoBaseDriveDistance(-30, true, true, baseDriveSlow);




wantedFlywheelRPM = 0;
AutoIntakeMode(intakeOff);
AutoBaseDriveDistance(0, false, false);
