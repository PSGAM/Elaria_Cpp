// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Profession_Enum.h"
#include "AIC_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIC_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ELARIA_API IAIC_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIC_Interface")
	void ChangeProfessionType(Profesion_Type newProfession);
};
