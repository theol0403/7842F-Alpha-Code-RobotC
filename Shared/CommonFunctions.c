



void setFlywheelPower(int flywheelSpeed)
{
	SetMotor(m_Flywheel, flywheelSpeed);
	SetMotor(m_Flywheel2, flywheelSpeed);
	// motor[m_Flywheel] = flywheelSpeed;
	// motor[m_Flywheel2] = flywheelSpeed;
}

void setIntakePower(int intakeSpeed)
{
	SetMotor(m_Intake, intakeSpeed);
	//motor[m_Intake] = intakeSpeed;
}


void setIndexerPower(int indexerSpeed)
{
	SetMotor(m_Indexer, indexerSpeed);
	//motor[m_Index] = indexSpeed;
}

void setBasePower(int rightSpeed, int leftSpeed)
{
	SetMotor(m_RightBase, rightSpeed);
	SetMotor(m_LeftBase, leftSpeed);
	SetMotor(m_RightBase2, rightSpeed);
	SetMotor(m_LeftBase2, leftSpeed);
	// motor[m_RightBase] = rightSpeed;
	// motor[m_LeftBase] = leftSpeed;
	// motor[m_RightBase2] = rightSpeed;
	// motor[m_LeftBase2] = leftSpeed;
}



// compensates for non-linearity of control value vs speed curve
const unsigned int trueSpeedArray[129] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
 25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
 28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
 37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
 41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
 46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
 71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
 80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
 88, 89, 89, 90, 90,127,127,127,127
};

int TrueSpeed(int value)
{
	return sgn(value) * trueSpeedArray[abs(value)];
}
