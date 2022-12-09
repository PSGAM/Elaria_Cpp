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
	
	if (messageSystemComponent != nullptr)
	{
		// Call a function (AIMovementCompleted) when the movement has ended
		//ownersAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UAC_ProfessionLumberjack::AIMovementCompleted);
		//messageSystemComponent->ReceiveMSG_Delegate.AddUObject(this, &UAC_ProfessionLumberjack::LumberjackReceiveMSG);
		//messageSystemComponent->ReceiveMSG_Delegate.Add(FLumberjackReceiveMSG_Delegate);
		messageSystemComponent->ReceiveMSG_Delegate.AddDynamic(this, &UAC_ProfessionLumberjack::LumberjackReceiveMSG);
	}

}

void UAC_ProfessionLumberjack::FinishedCurrentWorkState()
{
	switch (currentWorkState)
	{
	case FindTreeToChop_State:
		ownersAIController->GetPawn()->SetActorRotation(FRotationMatrix::MakeFromX(targetActor->GetActorLocation() - GetOwner()->GetActorLocation()).Rotator());
		currentWorkState = ChopingDownTree_State;
		UE_LOG(LogTemp, Warning, TEXT("Rotated to nearby tree: [ %s ]"), *targetActor->GetFName().ToString());
		if (messageSystemComponent != nullptr)
		{
			messageSystemComponent->SendMSG(messageSystemComponent->actorID, ChopingDownTree_State, 2.0f);
		}
		break;
	case ChopingDownTree_State:
		break;
	case ReplantTree_State:
		break;
	case CarryLog_State:
		break;
	case RefineLog_State:
		break;
	case CarryLumber_State:
		break;
	}
		
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
	FinishedCurrentWorkState();
	
//	FTimerHandle TH_WorkTickTEST;
//	GetWorld()->GetTimerManager().SetTimer(TH_WorkTickTEST, this, &UAC_ProfessionLumberjack::FindRandomTreeNearby, 2.0f, false);
}

void UAC_ProfessionLumberjack::LumberjackReceiveMSG(FMessageInfo newMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("MSG recieved on Lumberjack!!!!"));
}