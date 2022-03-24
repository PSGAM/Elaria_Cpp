// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "POI_Tree_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPOI_Tree_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ELARIA_API IPOI_Tree_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "POI_Tree_Interface")
	void BPI_CutDown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "POI_Tree_Interface")
	void BPI_ReplantTree();
};
