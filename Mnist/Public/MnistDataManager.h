#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MnistDataManager.generated.h"

#define TRAIN_LABELS_FILE		"D:/Desktop/mnist/train-labels.idx1-ubyte"
#define TRAIN_IMAGES_FILE		"D:/Desktop/mnist/train-images.idx3-ubyte"
#define TEST_LABELS_FILE		"D:/Desktop/mnist/t10k-labels.idx1-ubyte"
#define TEST_IMAGES_FILE		"D:/Desktop/mnist/t10k-images.idx3-ubyte"
#define TRAIN_ITEMS				60000
#define TEST_ITEMS				10000
#define NUMBER_OF_ROWS			28
#define NUMBER_OF_COLUMNS		28
#define NUMBER_OF_TOTAL_PIXEL	784

UCLASS(BlueprintType, Blueprintable)
class MNIST_API UMnistDataManager : public UObject
{
	GENERATED_BODY()

public:
	UMnistDataManager();

	void ResetData();
	void ReadNextTrain();
	void ReadNextTest();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mnist")
		uint8  label;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mnist")
		TArray<uint8> image;

private:
	void ReadNextLabel(const char[]);
	void ReadNextImage(const char[]);

	int offsetOfLabel;
	int offsetOfImage;
};
