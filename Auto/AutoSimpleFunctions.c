
enum intakeModes
{
  intakeCollect,
  intakeShoot,
  intakeOff,
  intakeOut

};

void AutoIntakeMode(intakeModes intakeMode)
{
  if(intakeMode == intakeCollect)
  {
    setIntakePower(127);
    setIndexerPower(15);
  }
  else if(intakeMode == intakeShoot)
  {
    setIntakePower(127);
    setIndexerPower(127);
  }
  else if(intakeMode == intakeOff)
  {
    setIntakePower(0);
    setIndexerPower(0);
  }
  else if(intakeMode == intakeOut)
  {
    setIntakePower(-127);
    setIndexerPower(15);
  }

}
