while (true)
{
  AutoBaseTurnDegrees(90, true, true);
  AutoBaseDriveDistance(5,5,true,true);
  AutoBaseTurnDegrees(90, true, true);

  AutoBaseDriveDistance(5,5,true,false);
  AutoBaseTurnDegrees(-180, true, false);
  AutoBaseDriveDistance(5,5,true,false);
  AutoBaseTurnDegrees(-90, true, false);
  AutoBaseDriveDistance(5,5,true,false);
  AutoBaseTurnDegrees(90, true, true);
}




AutoBaseDriveDistance(5,5,true,false);
wait1Msec(200);
writeDebugStreamLine("test");
AutoBaseDriveDistance(5,5,true,true);
AutoBaseTurnDegrees(90, false, true);

  //
  // AutoDriveDistance(30, 30, Brake, Block);
