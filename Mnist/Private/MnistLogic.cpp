#include "MnistLogic.h"
#include "time.h"
#ifndef NUM_QUNATITY
#define NUM_QUNATITY 10
#endif // !NUM_QUNATITY
#ifndef L_RATE
#define L_RATE 0.01
#endif // !L_RATE

void UMnistLogic::InitializeMnist(UMnistDataManager* inMnistData)
{
	srand((unsigned int)time(NULL)); rand();
	ans = new float[NUM_QUNATITY];
	weight = new float* [NUM_QUNATITY];
	yy = new float[NUM_QUNATITY];
	bias = new float[NUM_QUNATITY];
	for (int i = 0; i < NUM_QUNATITY; i++)
	{
		ans[i] = yy[i] = 0;
		weight[i] = new float[NUMBER_OF_TOTAL_PIXEL];
		bias[i] = rand() * 1.0 / RAND_MAX - 0.5;	// -0.5 .. 0.5
		for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++) weight[i][j] = rand() * 1.0 / RAND_MAX - 0.5;	// -0.5 .. 0.5
	}
	for (int i = 0; i < NUMBER_OF_TOTAL_PIXEL; i++) data.Add(0);
	trueAnswer = traceLabel = 0;
	mnistData = inMnistData;
}

void UMnistLogic::SetAnswer()
{
	for (int i = 0; i < NUM_QUNATITY; i++) ans[i] = 0; ans[trueAnswer] = 1;
}

void UMnistLogic::Forward()
{
	for (int i = 0; i < NUM_QUNATITY; i++)
	{
		yy[i] = bias[i];
		for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++) yy[i] += weight[i][j] * (data[j] / 255.0) * 0.001;
		yy[i] = exp(yy[i]) / (exp(yy[i]) + 1);
	}
}
#define w weight
void UMnistLogic::WeightOffset(int num, float dy, float* wTemp) // Note: Test for new weight calc
{
	int offset = 0;
	float wArr[9]; 
	for (int i = 0; i < NUMBER_OF_TOTAL_PIXEL; i += offset)
	{
		for (int i = 0; i < 9; i++) wArr[i] = 0;
		for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) wArr[j * 3 + k] = L_RATE * (float)data[i + j * NUMBER_OF_COLUMNS + k] * dy;
		for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) w[num][i + j * NUMBER_OF_COLUMNS + k] += ((j == 1 && k == 1) ? 1.0 : 0.1) * (((double)wArr[j * 3 + k] + (double)wArr[4]) / 2.0);


		if (i % NUMBER_OF_COLUMNS == NUMBER_OF_COLUMNS - 3)
		{
			if (i == NUMBER_OF_TOTAL_PIXEL - NUMBER_OF_COLUMNS * 2 - 3) break;
			offset = 3;
		}
		else offset = 1;
	}
}

float* UMnistLogic::Backward()
{
	float* wTemp = new float[NUMBER_OF_TOTAL_PIXEL];
	for (int i = 0; i < NUM_QUNATITY; i++)
	{
		float dy = ans[i] - yy[i];
		WeightOffset(i, dy, wTemp);
		/*for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++)
		{
			weight[i][j] += L_RATE * data[j] * dy;
			if (i == traceLabel) wTemp[j] = weight[i][j];
		}*/
		bias[i] += L_RATE * dy;
	}
	return wTemp;
}

void UMnistLogic::TraceableTrain()
{
	mnistData->ReadNextTrain();
	result.Empty();
	for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++) data[j] = (float)mnistData->image[j];
	trueAnswer = mnistData->label;

	SetAnswer();
	Forward();
	if (trueAnswer == traceLabel)
	{
		float* res = Backward();
		for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++) result.Add(res[j]);
	}
	else Backward();
}
