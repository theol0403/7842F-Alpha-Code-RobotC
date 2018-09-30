


struct raStruct
{
	float arraySize;
	float sampleNum;
	float avg;
	float values[100];
};


void raInit(raStruct &deviceName, int sampleNum)
{
	deviceName.sampleNum = sampleNum;
	deviceName.arraySize = sampleNum - 1;

	for (int i = deviceName.arraySize; i >= 0; i--)
	{
		deviceName.values[i] = 0;
	}
	deviceName.avg = 0;
}





float raCalculate(raStruct &deviceName, float newValue)
{
	float tempAvg = 0;

	for (int i = deviceName.arraySize; i > 0; i--)
	{
		deviceName.values[i] = deviceName.values[i - 1];
	}
	deviceName.values[0] = newValue;

	for (int i = deviceName.arraySize; i >= 0; i--)
	{
		tempAvg += deviceName.values[i];
	}

	deviceName.avg = tempAvg/deviceName.sampleNum;

 	return deviceName.avg;
}
