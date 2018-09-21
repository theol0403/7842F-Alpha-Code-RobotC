






void setFlywheelPower(int flywheelSpeed)
{
	motor[m_Flywheel] = flywheelSpeed;
	motor[m_Flywheel2] = flywheelSpeed;
}

void setIntakePower(int intakeSpeed)
{
	motor[m_Intake] = intakeSpeed;
}

void setBasePower(int rightSpeed, int leftSpeed)
{
	motor[m_RightBase] = rightSpeed;
	motor[m_LeftBase] = leftSpeed;
}
