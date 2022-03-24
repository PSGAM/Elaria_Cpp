// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PointOfInterest_C.h"

// Sets default values for this component's properties
UAC_PointOfInterest_C::UAC_PointOfInterest_C()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Create a BoxComponent that will have the collision channel for "MessageSystemChannel" set to Block, so the 
	//   traces for the near actors with a message systems component will respond.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PointOfInterestBoxCollision"));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));
	BoxComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}


// Called when the game starts
void UAC_PointOfInterest_C::BeginPlay()
{
	Super::BeginPlay();

	// Destroy other Point of Interest Box Collisions
	TInlineComponentArray<UActorComponent*> OwnersComponents;
	UActorComponent* currentComponentBeingChecked;
	GetOwner()->GetComponents(OwnersComponents);
	if (OwnersComponents.Num() > 0) {
		for (int32 CompIdx = 0; CompIdx < OwnersComponents.Num(); CompIdx++)
		{
			currentComponentBeingChecked = OwnersComponents[CompIdx];

			if (currentComponentBeingChecked->GetName() == "PointOfInterestBoxCollision")
			{
				if (currentComponentBeingChecked != BoxComponent)
				{
					currentComponentBeingChecked->DestroyComponent();
					UE_LOG(LogTemp, Warning, TEXT("PointOfInterest BOX Component has been destroyed successfully."));
				}
			}
		}
	}

	BoxComponent->AttachTo(GetOwner()->GetRootComponent());
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));
	BoxComponent->SetRelativeRotation(FRotator(0, 0, 0));
	BoxComponent->SetRelativeScale3D(FVector(0, 0, 0));

	// Add a unique tag in case we want to find if it has a Message System component.
	GetOwner()->Tags.AddUnique(PointOfInterestComponent_TagName);

}


// Called when the component is going to be destroyed, used for clean up on the owner actor.
void UAC_PointOfInterest_C::EndPlay(EEndPlayReason::Type Reason)
{
	if (BoxComponent != nullptr)
	{
		BoxComponent->DestroyComponent();
		BoxComponent->SetActive(false);
		UE_LOG(LogTemp, Warning, TEXT("MessageSystem Component has been destroyed."));
	}

	GetOwner()->Tags.Remove(PointOfInterestComponent_TagName);
}


// Called every frame
void UAC_PointOfInterest_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_PointOfInterest_C::POI_DeactivateCollision()
{
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
}

void UAC_PointOfInterest_C::POI_ActivateCollision()
{
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
}

PointOfInterest_Type UAC_PointOfInterest_C::GetPOIType()
{
	return PointOfInterest_Type_enum;
}
