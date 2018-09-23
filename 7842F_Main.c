#pragma config(Sensor, dgtl1,  s_FlywheelEn,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  s_LeftEn,       sensorQuadEncoder)
#pragma config(Motor,  port2,           m_Flywheel,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           m_Intake,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           m_RightBase,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           m_RightBase2,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           m_Flywheel2,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           m_LeftBase,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           m_LeftBase2,   tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)


//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"





#include "Shared/CommonFunctions.c"











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

}









/*
/_    _
| |  | |
| |  | |  ___    ___   _ __
| |  | | / __|  / _ \ | '__|
| |__| | \__ \ |  __/ | |
\\____/  |___/  \___| |_|
*/
#include "Driver/DriverFlywheelTask.c"
#include "Driver/DriverMainControls.c"


task usercontrol()
{
  startTask(DriverMainTask);
  //startTask(DriverFlywheelTask);
  wait1Msec(10000000);
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

}
