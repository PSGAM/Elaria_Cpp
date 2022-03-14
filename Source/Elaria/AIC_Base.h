// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Base.generated.h"

struct BasicNeccesityStruct
{
	// "unsigned short int" goes from [ 0 to +65,535 ]
	
	unsigned short int hunger = 0;
	unsigned short int thirst = 0;
	unsigned short int sleep = 0;
};

UCLASS()
class ELARIA_API AAIC_Base : public AAIController
{
	GENERATED_BODY()
	
public:


private:
	BasicNeccesityStruct neccesities;


};
