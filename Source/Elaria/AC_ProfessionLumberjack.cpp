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

	if (GetOwner()->GetInstigatorController()->IsPlayerController() == false)
	{
		// Call a function (AIMovementCompleted) when the movement has ended
		ownersAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UAC_ProfessionLumberjack::AIMovementCompleted);
	}

	

	UE_LOG(LogTemp, Warning, TEXT("Starting Lumberjack profession component."));

	
	// Timer test
	FTimerHandle TH_WorkTickTEST;
	GetWorld()->GetTimerManager().SetTimer(TH_WorkTickTEST, this, &UAC_ProfessionLumberjack::FindRandomTreeNearby, 2.0f, false);
	
}

void UAC_ProfessionLumberjack::FinishedCurrentWorkState()
{
		
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

	if (ownersAIController)
	{
		ownersAIController->MoveToActor(targetActor);
	}
	
}

void UAC_ProfessionLumberjack::AIMovementCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Movement completed."));
}