

task autoLEDTask()
{
  int ledFlash = 0;
  bool ledOn;
  bool tileColor;
  bool selectColor;

  while(true)
  {
    if(ledOn)
    {
      if(ledFlash < 6)
      {
        SensorValue[s_RightLED] = 0;
        SensorValue[s_LeftLED] = 0;
      }
      else if(ledFlash < 10 && ledFlash >= 6)
      {
        SensorValue[s_RightLED] = 1;
        SensorValue[s_LeftLED] = 1;
      }
      else if(ledFlash >= 10 )
      {
        ledFlash = 0;
      }
      ledFlash++;
    }
    else
    {
      SensorValue[s_RightLED] = 0;
      SensorValue[s_LeftLED] = 0;
    }




    tileColor = (SensorValue[s_tileLine] < 1900);

    selectColor = (SensorValue[s_sideSelector] < 2047);

    ledOn = (tileColor != selectColor);

    wait1Msec(20);


  }
}
