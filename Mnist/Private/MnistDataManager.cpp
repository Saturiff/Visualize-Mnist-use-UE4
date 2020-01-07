#include "MnistDataManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

UMnistDataManager::UMnistDataManager() { }

void UMnistDataManager::ResetData()
{
	this->label = this->offsetOfImage = this->offsetOfLabel = 0;
	this->image.Empty();
}

uint8 NextByte(FILE* filePtr)
{
	uint8 buffer[1] = { 0 };
	fread(buffer, sizeof(uint8), 1, filePtr);
	return buffer[0];
}

void UMnistDataManager::ReadNextLabel(const char fileName[])
{
	FILE* labelFile = fopen(fileName, "rb");
		fseek(labelFile, this->offsetOfLabel + sizeof(int) * 2, 0);
		this->label = NextByte(labelFile);
	fclose(labelFile);
	this->offsetOfLabel++;
}

void UMnistDataManager::ReadNextImage(const char fileName[])
{
	this->image.Empty();
	FILE* imageFile = fopen(fileName, "rb");
		fseek(imageFile, this->offsetOfImage + sizeof(int) * 4, 0);
		for (int j = 0; j < NUMBER_OF_TOTAL_PIXEL; j++) this->image.Add(NextByte(imageFile));
	fclose(imageFile);
	this->offsetOfImage += NUMBER_OF_TOTAL_PIXEL;
}

void UMnistDataManager::ReadNextTrain()
{
	this->ReadNextLabel(TRAIN_LABELS_FILE);
	this->ReadNextImage(TRAIN_IMAGES_FILE);
}

void UMnistDataManager::ReadNextTest()
{
	this->ReadNextLabel(TEST_LABELS_FILE);
	this->ReadNextImage(TEST_IMAGES_FILE);
}
