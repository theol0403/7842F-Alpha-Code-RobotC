#pragma config(Sensor, in1,    s_sideSelector, sensorPotentiometer)
#pragma config(Sensor, in2,    s_autoSelector, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  s_FlywheelEn,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  s_LeftEn,       sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  s_RightEn,      sensorQuadEncoder)
#pragma config(Motor,  port2,           m_RightBase2,  tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           m_RightBase,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           m_Intake,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           m_Flywheel,    tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           m_Flywheel2,   tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port7,           m_LeftBase,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           m_LeftBase2,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           m_Indexer,     tmotorVex393TurboSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)
//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"






/***
 *     _     _ _                    _
 *    | |   (_) |                  (_)
 *    | |    _| |__  _ __ __ _ _ __ _  ___  ___
 *    | |   | | '_ \| '__/ _` | '__| |/ _ \/ __|
 *    | |___| | |_) | | | (_| | |  | |  __/\__ \
 *    \_____/_|_.__/|_|  \__,_|_|  |_|\___||___/
 *
 *
 */

 //#include "Libraries/BNSLib/BNSLib.h"

//Enable the use of BCI EMA Filters
 #define BCI_USE_DEMA_FILTER
 #define BCI_USE_EMA_FILTER
 #include "Libraries/BCILib/BCILib.h"


 #include "Libraries/7842FLib/7842FLib.h"







 /***
  *     _____ _                        _
  *    /  ___| |                      | |
  *    \ `--.| |__   __ _ _ __ ___  __| |
  *     `--. \ '_ \ / _` | '__/ _ \/ _` |
  *    /\__/ / | | | (_| | | |  __/ (_| |
  *    \____/|_| |_|\__,_|_|  \___|\__,_|
  *
  *
  */

 #include "Shared/CommonMotorFunctions.c" //Motor Move functions and TrueSpeed

 int wantedFlywheelRPM = 0;
 #include "Shared/MainFlywheelTask.c"

 bool overrideLCD;
 #include "Shared/LCDTask.c"









/***
 *    ______                 ___        _
 *    | ___ \               / _ \      | |
 *    | |_/ / __ ___ ______/ /_\ \_   _| |_ ___
 *    |  __/ '__/ _ \______|  _  | | | | __/ _ \
 *    | |  | | |  __/      | | | | |_| | || (_) |
 *    \_|  |_|  \___|      \_| |_/\__,_|\__\___/
 */



void pre_auton()
{
  startTask(LCDTask);

  //BNS();

  bStopTasksBetweenModes = true; //Kills Running Tasks Between Modes
}








/***
 *     _   _
 *    | | | |
 *    | | | |___  ___ _ __
 *    | | | / __|/ _ \ '__|
 *    | |_| \__ \  __/ |
 *     \___/|___/\___|_|
 */

#include "Driver/DriverSimpleControls.c"


task usercontrol()
{
  startTask(LCDTask);

  startTask(DriverMainTask);
  startTask(FlywheelPIDTask);





  while(true)
  {
    wait1Msec(10000);
  }

}










/***
 *      ___        _
 *     / _ \      | |
 *    / /_\ \_   _| |_ ___
 *    |  _  | | | | __/ _ \
 *    | | | | |_| | || (_) |
 *    \_| |_/\__,_|\__\___/
 */


#include "Auto/AutoExec.h"

task autonomous()
{
  startTask(LCDTask);

  sideColors chosenSide = SensorValue[s_sideSelector] < 2047 ? redSide : blueSide;

  AutoBaseInit_Chassis(s_LeftEn, s_RightEn, 12.56, 15.25, chosenSide);
  AutoBaseInit_Config(10, 127, 50, 200, 20, 400);
  AutoBaseInit_PID(0.4, 0.0, 0);
  startTask(AutoBaseTask);

  switch(SensorValue[s_autoSelector]/819)
  {
    case 0:
    AutoExec0();
    break;
    case 1:
    AutoExec1();
    break;
    case 2:
    AutoExec2();
    break;
    case 3:
    AutoExec3();
    break;
    case 4:
    AutoExec4();
    break;
    case 5:
    AutoExecTesting();
    break;
  }


  wait1Msec(1000000);

}
