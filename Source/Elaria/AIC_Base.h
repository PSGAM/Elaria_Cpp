// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "Profession_Enum.h"
#include "AIC_Interface.h"
#include "AC_ProfessionBase.h"
#include "AC_ProfessionLumberjack.h"
#include "AIC_Base.generated.h"

struct BasicNecessitiesStruct
{
	// "unsigned short int" goes from [ 0 to +65,535 ]
	unsigned short int hunger = 0;
	unsigned short int thirst = 0;
	unsigned short int sleep = 0;
};

struct BasicNecessityInfo
{
	// How often the Necessity will be ticked,
	// if [-1] will not create a timer
	float necessityTickRate = -1.0f;

	// How much the Necessity will increment every tick
	// if [0] will not create a timer
	unsigned short int necessityIncrement = 0;

	// Random variation from where the actor will start,
	// going from 0 to the number specified.
	unsigned short int randomInitialValueRange = 20;

	// The maximun value that the Necessity can reach
	unsigned short int maxNecessityValue = 100;
};

UCLASS()
class ELARIA_API AAIC_Base : public AAIController, public IAIC_Interface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAIC_Base();
	~AAIC_Base();


public:
	void HungerTick();
	void ThirstTick();
	void SleepTick();
	void StartNecessitiesTimers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIC_Interface")
	void ChangeProfessionType(Profesion_Type newProfession);
	virtual void ChangeProfessionType_Implementation(Profesion_Type newProfession);
	
private:
//	FString ownersName = "DEFAULT_OWNERS_NAME";

	// Profession
	TEnumAsByte<Profesion_Type> currentProfessionEnum = Profesion_Type::None;
	
	BasicNecessitiesStruct basicNecessities;
	
	// Hunger
	BasicNecessityInfo hungerInfo;
	FTimerHandle TH_HungerTick;

	// Thirst
	BasicNecessityInfo thirstInfo;
	FTimerHandle TH_ThirstTick;

	// Thirst
	BasicNecessityInfo sleepInfo;
	FTimerHandle TH_SleepTick;

};
