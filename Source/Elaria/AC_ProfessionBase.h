// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "AC_MessageSystem_Cpp.h"
#include "AC_ProfessionBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELARIA_API UAC_ProfessionBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ProfessionBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AIMovementCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
		
protected:
	AAIController* ownersAIController = nullptr;

	AActor* targetActor = nullptr;
	FVector targetLocation;

	UAC_MessageSystem_Cpp* messageSystemComponent = nullptr;
};
