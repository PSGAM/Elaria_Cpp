// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ProfessionLumberjack.h"

UAC_ProfessionLumberjack::UAC_ProfessionLumberjack()
{
	UE_LOG(LogTemp, Warning, TEXT("Lumberjack Initializer"));
}

UAC_ProfessionLumberjack::~UAC_ProfessionLumberjack()
{
}

void UAC_ProfessionLumberjack::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Starting Lumberjack profession component."));

	/*
	// Timer test
	FTimerHandle TH_WorkTickTEST;
	GetWorld()->GetTimerManager().SetTimer(TH_WorkTickTEST, this, &UAC_ProfessionLumberjack::Work_State, 2.0f, true);
	*/
}

void UAC_ProfessionLumberjack::Work_State()
{
	// UE_LOG(LogTemp, Warning, TEXT("Lumberjack's function is called after 2 seconds!!!"));
}