// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_ProfessionBase.h"
#include "POI_Tree_Interface.h"
#include "AC_PointOfInterest_C.h"
#include "AC_ProfessionLumberjack.generated.h"

// List of the available profesions
UENUM(BlueprintType)
enum Lumberjack_State_Type {
	Idle_State = 0 UMETA(DisplayName = "Idle"),
	Work_State = 1 UMETA(DisplayName = "Work"),
};

UENUM(BlueprintType)
enum Lumberjack_WorkState_Type {
	FindTreeToChop_State = 0 UMETA(DisplayName = "Searching for a tree to chop down"),
//	GoToTree_State = 1 UMETA(DisplayName = "Going to chop down a tree"),
	ChopDownTree_State = 1 UMETA(DisplayName = "Choping down tree"),
	ReplantTree_State = 2 UMETA(DisplayName = "Replanting tree"),
	CarryLog_State = 3 UMETA(DisplayName = "Carring log"),
	RefineLog_State = 4 UMETA(DisplayName = "Refining log into lumber"),
	CarryLumber_State = 5 UMETA(DisplayName = "Carring lumber"),
};

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
	void FinishedCurrentWorkState();
	void FindRandomTreeNearby();

	void AIMovementCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	Lumberjack_State_Type currentGeneralState = Lumberjack_State_Type::Work_State;
	Lumberjack_WorkState_Type currentWorkState = Lumberjack_WorkState_Type::FindTreeToChop_State;

//	AActor* targetActor = nullptr;
//	FVector targetLocation;

//	AAIController* ownersAIController = nullptr;

};
