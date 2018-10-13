
task LCDTask()
{

  bLCDBacklight = true; //Turns LCD backlighting on
  clearLCDLine(0); //Clears LCD values
  clearLCDLine(1); //Clears LCD values

  while(true)
  {

    waitUntil(!overrideLCD); //Checks to see if other tasks want to use LCD

    switch(SensorValue[s_autoSelector]/819)
    {

      case 0:

      displayLCDPos(0,0);
      displayNextLCDString("     Skills     ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Slot 0  ");
      }
      else
      {
        displayNextLCDString(" Blue - Slot 0  ");
      }

      break;

      case 1:

      displayLCDPos(0,0);
      displayNextLCDString("     Slot 1     ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Slot 1  ");
      }
      else
      {
        displayNextLCDString(" Blue - Slot 1  ");
      }

      break;

      case 2:

      displayLCDPos(0,0);
      displayNextLCDString("     Slot 2     ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Slot 2  ");
      }
      else
      {
        displayNextLCDString(" Blue - Slot 2  ");
      }

      break;

      case 3:

      displayLCDPos(0,0);
      displayNextLCDString("     Slot 3     ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Slot 3  ");
      }
      else
      {
        displayNextLCDString(" Blue - Slot 3  ");
      }

      break;

      case 4:

      displayLCDPos(0,0);
      displayNextLCDString("     Slot 4     ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Slot 4  ");
      }
      else
      {
        displayNextLCDString(" Blue - Slot 4  ");
      }

      break;

      case 5:

      displayLCDPos(0,0);
      displayNextLCDString("     Testing    ");
      displayLCDPos(1,0);

      if(SensorValue[s_sideSelector] > 2047)
      {
        displayNextLCDString("  Red - Testing ");
      }
      else
      {
        displayNextLCDString(" Blue - Testing ");
      }

      break;

      default:
      displayLCDPos(0,0);
      displayNextLCDString("     7842F      ");
      displayLCDPos(1,0);
      displayNextLCDString(" Sensor's Broke ");

    }
    wait1Msec(100);
  }
}
