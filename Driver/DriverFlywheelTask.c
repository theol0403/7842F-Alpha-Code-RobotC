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
// struct PID
// {
// 	float Kp;
// 	float Kd;
// 	float Ki;
//
// 	int totalError;
// 	int lastError;
//
// 	int integralCap;
//
// 	int Error;
//
// 	int lastTime;
// }
//
// PID flywheelPID
//
// void pidInit (PID pid, float Kp, float Ki, float Kd) {
// 	pid.Kp = Kp;
// 	pid.Ki = Ki;
// 	pid.Kd = Kd;
// 	pid.Kf = 0.0;
// 	pid.sigma = 0;
// 	pid.lastValue = 0;
// 	pid.lastTime = nPgmTime;
// }
//
// task flywheelPIDtask()
// {
// 	initPID(flywheelPID, 1, 0, 0);
// 	while(true)
// 	{
// 		motor += calculatePID
// 	}
// }
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
