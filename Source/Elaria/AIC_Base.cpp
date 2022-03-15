// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Base.h"

AAIC_Base::AAIC_Base()
{
	// Hunger
	hungerInfo.necessityTickRate = 3.0f;
	hungerInfo.necessityIncrement = 1;
	hungerInfo.randomInitialValueRange = 20;
	hungerInfo.maxNecessityValue = 100;

	// Thirst
	thirstInfo.necessityTickRate = 2.0f;
	thirstInfo.necessityIncrement = 1;
	thirstInfo.randomInitialValueRange = 20;
	thirstInfo.maxNecessityValue = 100;

	// Sleep
	sleepInfo.necessityTickRate = 12.0f;
	sleepInfo.necessityIncrement = 1;
	sleepInfo.randomInitialValueRange = 20;
	sleepInfo.maxNecessityValue = 100;

	// Initialize Necessities
	basicNecessities.hunger = FMath::RandRange(0, hungerInfo.randomInitialValueRange);
	basicNecessities.thirst = FMath::RandRange(0, thirstInfo.randomInitialValueRange);
	basicNecessities.sleep = FMath::RandRange(0, sleepInfo.randomInitialValueRange);
}

AAIC_Base::~AAIC_Base()
{
	/*
	if(GetWorldTimerManager().TimerExists(TH_HungerTick))
	{
		GetWorldTimerManager().ClearTimer(TH_HungerTick);
	}*/
}

void AAIC_Base::HungerTick()
{
	basicNecessities.hunger += hungerInfo.necessityIncrement;

	UE_LOG(LogTemp, Warning, TEXT("Hunger: %d"), basicNecessities.hunger);
}

void AAIC_Base::ThirstTick()
{
	basicNecessities.thirst += thirstInfo.necessityIncrement;

	UE_LOG(LogTemp, Warning, TEXT("Thirst: %d"), basicNecessities.thirst);
}

void AAIC_Base::SleepTick()
{
	basicNecessities.sleep += sleepInfo.necessityIncrement;

	UE_LOG(LogTemp, Warning, TEXT("Sleep: %d"), basicNecessities.sleep);
}

void AAIC_Base::StartNecessitiesTimers()
{
	// Create hunger timer
	if (hungerInfo.necessityIncrement > 0)
	{
		GetWorldTimerManager().SetTimer(TH_HungerTick, this, &AAIC_Base::HungerTick, hungerInfo.necessityTickRate, true);
	}

	// Create thrist timer
	if (thirstInfo.necessityIncrement > 0)
	{
		GetWorldTimerManager().SetTimer(TH_ThirstTick, this, &AAIC_Base::ThirstTick, thirstInfo.necessityTickRate, true);
	}

	// Create sleep timer
	if (sleepInfo.necessityIncrement > 0)
	{
		GetWorldTimerManager().SetTimer(TH_SleepTick, this, &AAIC_Base::SleepTick, sleepInfo.necessityTickRate, true);
	}
}


void AAIC_Base::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Starting necessity timers."));
	StartNecessitiesTimers();
}
