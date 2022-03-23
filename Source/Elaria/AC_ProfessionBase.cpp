// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ProfessionBase.h"

// Sets default values for this component's properties
UAC_ProfessionBase::UAC_ProfessionBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAC_ProfessionBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetInstigatorController()->IsPlayerController() == false)
	{
		// Save a reference to the owner's AIController for movement behaviour
		ownersAIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
	}
	

	// Check if the owner has a MessageSystemComponent, otherwise spawn it
	TInlineComponentArray<UActorComponent*> OwnersComponents;
	UActorComponent* currentComponentBeingChecked;
	bool bFoundMessageComponent = false;
	GetOwner()->GetComponents(OwnersComponents);
	if (OwnersComponents.Num() > 0) {
		for (int32 CompIdx = 0; CompIdx < OwnersComponents.Num(); CompIdx++)
		{
			currentComponentBeingChecked = OwnersComponents[CompIdx];

			//if (currentComponentBeingChecked->GetName() == "PointOfInterestBoxCollision")
			if (currentComponentBeingChecked->GetName() == "AC_MessageSystem_Cpp" || 
				currentComponentBeingChecked->GetName() == "AC_MessageSystem_BP")
			{
				messageSystemComponent = Cast<UAC_MessageSystem_Cpp>(currentComponentBeingChecked);
				bFoundMessageComponent = true;
			}
		}
	}
	if (bFoundMessageComponent == false)
	{
		messageSystemComponent = NewObject<UAC_MessageSystem_Cpp>(GetOwner());
		GetOwner()->AddOwnedComponent(messageSystemComponent);

		UE_LOG(LogTemp, Warning, TEXT("MessageSystem Component has been successfully created by the base profession."));
	}

}


// Called every frame
void UAC_ProfessionBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ProfessionBase::AIMovementCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	// Implement on children if needed.
}

