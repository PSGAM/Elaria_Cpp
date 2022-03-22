// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ProfessionLumberjack.h"
#include "DrawDebugHelpers.h"

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

	
	// Timer test
	FTimerHandle TH_WorkTickTEST;
	GetWorld()->GetTimerManager().SetTimer(TH_WorkTickTEST, this, &UAC_ProfessionLumberjack::FindRandomTreeNearby, 2.0f, true);
	
}

void UAC_ProfessionLumberjack::FinishedCurrentWorkState()
{
	// UE_LOG(LogTemp, Warning, TEXT("Lumberjack's function is called after 2 seconds!!!"));
	/*switch (currentGeneralState)
	{
		case Lumberjack_State_Type::Idle_State
		
	}*/
}

void UAC_ProfessionLumberjack::FindRandomTreeNearby()
{
	TArray<FHitResult> OutHits;
	FCollisionShape customCollisionSphere = FCollisionShape::MakeSphere(1500.f);

	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), customCollisionSphere.GetSphereRadius(), 20, FColor::Purple, false, 1.5f);
	
	// Make the hit
	bool isHit = GetWorld()->SweepMultiByChannel(
								OutHits,
								GetOwner()->GetActorLocation(),
								GetOwner()->GetActorLocation(),
								FQuat::Identity, 
								ECollisionChannel::ECC_GameTraceChannel3,
								customCollisionSphere);

	if (isHit)
	{
		int getRandomIndex = FMath::RandRange(0, OutHits.Num() - 1);
		targetActor = OutHits[getRandomIndex].GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Search nearby tree: [ %s ]"), *targetActor->GetFName().ToString());
	}
}