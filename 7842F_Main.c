
#include "Shared/MotorFunctions.c"



/*
/_    _
| |  | |
| |  | |  ___    ___   _ __
| |  | | / __|  / _ \ | '__|
| |__| | \__ \ |  __/ | |
\\____/  |___/  \___| |_|
*/
#include "Driver/DriverMainControls.c"

task usercontrol()
{
  startTask(DriverMainTask);
  wait1Msec(10000000);
}
