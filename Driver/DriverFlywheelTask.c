//
// bool flywheelToggle = false;
//
// //max speed = 750;
//
// task flywheelTask()
// {
//
// 	while(true)
// 	{
//
// 		if(vexRT[Btn6U])
// 		{
// 			flywheelToggle = true
// 		}
// 		else if(vexRT[Btn6D])
// 		{
// 			flywheelToggle = false;
// 		}
//
//
// 		if(flywheelToggle)
// 		{
// 			setFlywheelPower
// 		}
//
// 		for(int i = 40; i < 127; i++)
// 		{
// 			setFlywheelPower(i);
// 			delay(60);
// 		}
// 		delay(1000000);
// 	}
// }
//
//
//
//
// task flywheelTask()
// {
// 	for(int i = 40; i < 127; i++)
// 		{
// 			setFlywheelPower(i);
// 			delay(60);
// 		}
// 		delay(1000000);
// }
//
//
// // Flywheel BangBang --------------------------------------------------------------------------------
// if(vexRT[Btn6U])
// {
// 	startTask(flywheelTask);
// }
// else if(vexRT[Btn6D])
// {
// 	stopTask(flywheelTask);
// 	setFlywheelPower(0);
// }
// // Flywheel BangBang --------------------------------------------------------------------------------
//
// /*
//
//
//
//
// task DriverFlywheelTask()
// {
//
// while(true)
// {
//
// }
// }
//
//
// // Flywheel BangBang --------------------------------------------------------------------------------
// if(vexRT[Btn6U])
// {
// startTask(flywheelTask);
// }
// else if(vexRT[Btn6D])
// {
// stopTask(flywheelTask);
// setFlywheelPower(0);
// }
// // Flywheel BangBang --------------------------------------------------------------------------------
// */
