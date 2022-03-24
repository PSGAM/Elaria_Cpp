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
	targetActor = nullptr;

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
		/// Get only the hits matching the POIType
		TArray<FHitResult> POI_TreeOutHits;
		
		for (auto i : OutHits)
		{
			UAC_PointOfInterest_C* currentPOIComponent = i.GetActor()->FindComponentByClass<UAC_PointOfInterest_C>();
			if (currentPOIComponent != nullptr)
			{
				if (currentPOIComponent->GetPOIType() == PointOfInterest_Type::POI_Tree)
				{
					POI_TreeOutHits.Add(i);
				}
			}
		}

		// Get a random tree from the hits of type POI_Tree
		if (POI_TreeOutHits.Num() > 0)
		{
			int getRandomIndex = FMath::RandRange(0, POI_TreeOutHits.Num() - 1);
			targetActor = POI_TreeOutHits[getRandomIndex].GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Search nearby tree: [ %s ]"), *targetActor->GetFName().ToString());
		}
	}
	

	if (ownersAIController && targetActor)
	{
		ownersAIController->MoveToActor(targetActor, 50.f);
	}
	
}

void UAC_ProfessionLumberjack::AIMovementCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	// UE_LOG(LogTemp, Warning, TEXT("Movement completed."));

	if (targetActor->GetClass()->ImplementsInterface(UPOI_Tree_Interface::StaticClass()))
	{
		IPOI_Tree_Interface::Execute_BPI_CutDown(targetActor);
	}

	FTimerHandle TH_WorkTickTEST;
	GetWorld()->GetTimerManager().SetTimer(TH_WorkTickTEST, this, &UAC_ProfessionLumberjack::FindRandomTreeNearby, 2.0f, false);
}