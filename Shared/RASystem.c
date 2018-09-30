


struct raStruct
{
	float arraySize;
	float sampleNum;
	float value[100];
	float avg;
};


void raInit(raStruct deviceName, int sampleNum)
{
	deviceName.sampleNum = sampleNum;
	deviceName.arraySize = sampleNum - 1;

	for (int i = deviceName.arraySize; i >= 0; i--)
	{
		deviceName.value[i] = 0;
	}
	deviceName.avg = 0;
}





float raCalculate(raStruct deviceName, float newValue)
{
	float tempAvg = 0;

	for (int i = deviceName.arraySize; i > 0; i--)
	{
		deviceName.value[i] = deviceName.value[i - 1];
	}
	deviceName.value[0] = newValue;

	for (int i = deviceName.arraySize; i >= 0; i--)
	{
		tempAvg += deviceName.value[i];
	}

	deviceName.avg = tempAvg/deviceName.sampleNum;

 	return deviceName.avg;
}
