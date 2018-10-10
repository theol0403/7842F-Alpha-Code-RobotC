
enum intakeModes
{
  intakeCollect,
  intakeShoot,
  intakeOff

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

}
