

//Exponential moving average filter
typedef struct EMAFilter_t
{
	float alpha;
	float output;
	float output_old;
} EMAFilter;



void filter_Init_EMA(EMAFilter &filter, float alpha = 1.0)
{
	filter.alpha = alpha;
	filter.output = 0.0;
	filter.output_old = 0.0;
}

float filter_EMA(EMAFilter &filter, float readIn)
{
	filter.output = filter.alpha * readIn + (1.0 - filter.alpha) * filter.output_old;
	filter.output_old = filter.output;
	return filter.output;
}

float filter_EMA(EMAFilter &filter, float readIn, float alpha)
{
	filter.alpha = alpha;
	return filter_EMA(filter, readIn);
}
