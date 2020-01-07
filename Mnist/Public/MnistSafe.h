// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MnistDataManager.h"
#include "MnistSafe.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MNIST_API UMnistSafe : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Mnist")
		int mnist_main(UMnistDataManager* mnistData);
};
