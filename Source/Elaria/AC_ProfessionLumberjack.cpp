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
	
}
