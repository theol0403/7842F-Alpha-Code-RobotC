
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
AutoBaseDriveDistance(38);
AutoBaseTurnDegrees(-90);
AutoBaseDriveDistance(-26);
AutoIntakeMode(intakeShoot);
wait1Msec(1000);
AutoIntakeMode(intakeCollect);

AutoBaseDriveDistance(68);
AutoBaseDriveDistance(-23);
AutoBaseTurnDegrees(90);
AutoIntakeMode(intakeOut);
AutoBaseDriveDistance(-24);
