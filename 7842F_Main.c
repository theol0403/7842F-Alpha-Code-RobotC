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



#include "Shared/CommonFunctions.c"



#define BCI_USE_DEMA_FILTER
#define BCI_USE_EMA_FILTER
#include "Libraries/BCILib/BCILib.h"

//#include "Libraries/BNSLib/BNSLib.h"

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


  //BNS();

  bStopTasksBetweenModes = true; //Kills Running Tasks Between Modes

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
#include "Driver/DriverFlywheelTask.c"
#include "Driver/DriverSimpleControls.c"




task usercontrol()
{

  startTask(DriverMainTask);
  startTask(FlywheelPIDTask);





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

#include "Auto/AutoHybridSystem.c"

task autonomous()
{
  startTask(AutoBaseTask);

  AutoBaseInit(s_LeftEn, s_RightEn, 12.56, 15.25, 100, 0, 0.6, 0, 0, 100000, 0, 100000);

//  AutoDriveDistance(30, 30, b_Brake, b_Block);

AutoTurnDegrees(90, b_Brake, b_Block);
  //
  // AutoDriveDistance(30, 30, Brake, Block);

  wait1Msec(10000);

}
