#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MnistDataManager.h"
#include "MnistLogic.generated.h"

UCLASS(BlueprintType, Blueprintable)
class MNIST_API UMnistLogic : public UObject
{
	GENERATED_BODY()
	
public:
	void SetAnswer();
	void Forward();
	float* Backward();
	void WeightOffset(int num, float dy, float* wTemp);

	UFUNCTION(BlueprintCallable, Category = "Mnist")
		void InitializeMnist(UMnistDataManager* inMnistData);
	UFUNCTION(BlueprintCallable, Category = "Mnist")
		void TraceableTrain();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mnist")
		UMnistDataManager* mnistData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mnist")
		uint8 traceLabel;
	
	TArray<float> data;
	uint8 trueAnswer;
	float** weight;
	float*  bias;
	float*  yy;
	float*  ans;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mnist")
		TArray<float> result;
};
