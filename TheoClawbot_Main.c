#pragma config(Sensor, dgtl1,  s_FlywheelEn,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  s_LeftEn,       sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  s_RightEn,      sensorQuadEncoder)
#pragma config(Motor,  port2,           m_RightBase2,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           m_RightBase,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           m_Intake,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           m_Flywheel,    tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           m_Flywheel2,   tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port7,           m_LeftBase,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           m_LeftBase2,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           m_Indexer,     tmotorVex393TurboSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)


//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"



#define BCI_USE_DEMA_FILTER
#define BCI_USE_EMA_FILTER
#include "Libraries/BCILib/BCILib.h"

#include "Shared/CommonFunctions.c"

#include "Libraries/7842FLib/7842FLib.h"




/*
_____                                              _
|  __ \                             /\             | |
| |__) |  _ __    ___   ______     /  \     _   _  | |_    ___
|  ___/  | '__|  / _ \ |______|   / /\ \   | | | | | __|  / _ \
| |      | |    |  __/           / ____ \  | |_| | | |_  | (_) |
|_|      |_|     \___|          /_/    \_\  \__,_|  \__|  \___/
Code that runs when the robot is turned on
*/



void pre_auton()
{
  bStopTasksBetweenModes = true; //Kills Running Tasks Between Modes
  startTask(autonomous);
  wait1Msec(10000000);



}









/*
/_    _
| |  | |
| |  | |  ___    ___   _ __
| |  | | / __|  / _ \ | '__|
| |__| | \__ \ |  __/ | |
\\____/  |___/  \___| |_|
*/

int wantedFlywheelRPM = 0;
#include "Driver/DriverSimpleControls.c"


#include "Driver/DriverOdomTask.c"

task usercontrol()
{

  //startTask(DriverMainTask);

startTask(DriverOdomTask);
startTask(odomTest);



  while(true)
  {
    wait1Msec(10000);
  }

}










/*
/////////////////_
/////\          | |
////  \   _   _ | |_  ___
/// /\ \ | | | || __|/ _ \
// ____ \| |_| || |_| (_) |
/_/    \_\\__,_| \__|\___/

*/


task autonomous()
{

  AutoBaseInit_Chassis(s_LeftEn, s_RightEn, 12.56, 11);
  AutoBaseInit_Config(0, 50, 50, 100, 20, 400);
  AutoBaseInit_PID(0.4, 0.0, 0);
  startTask(AutoBaseTask);

while (true) {
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

  wait1Msec(10000);

}
