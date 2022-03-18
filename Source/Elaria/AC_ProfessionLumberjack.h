// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_ProfessionBase.h"
#include "AC_ProfessionLumberjack.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class ELARIA_API UAC_ProfessionLumberjack : public UAC_ProfessionBase
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	UAC_ProfessionLumberjack();
	~UAC_ProfessionLumberjack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Work_State();
	
};
