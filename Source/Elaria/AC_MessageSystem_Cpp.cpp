// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_MessageSystem_Cpp.h"

// Sets default values for this component's properties
UAC_MessageSystem_Cpp::UAC_MessageSystem_Cpp()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Create a BoxComponent that will have the collision channel for "MessageSystemChannel" set to Block, so the 
	//   traces for the near actors with a message systems component will respond.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MessageSystemBoxCollision"));
	

}


// Called when the game starts
void UAC_MessageSystem_Cpp::BeginPlay()
{
	Super::BeginPlay();

	/////////////////////////////////////////////////////////////
	// MESSAGE SYSTEM
	/////////////////////////////////////////////////////////////

	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));

	// Get all actors of class <AMessageManager_Cpp>
	for (TActorIterator<AMessageManager_C> iterator(GetWorld(), AMessageManager_C::StaticClass()); iterator; ++iterator)
	{
		AMessageManager_C* currentActorBeingChecked = *iterator;
		if (currentActorBeingChecked != NULL)
		{
			MessageManagerAssigned = currentActorBeingChecked;
		}
	}
	if (MessageManagerAssigned != NULL)
	{
		actorID = MessageManagerAssigned->RegisterActor(GetOwner(), this);
	}

	// Destroy other Message System Box Collisions
	TInlineComponentArray<UActorComponent*> OwnersComponents;
	UActorComponent* currentComponentBeingChecked;
	GetOwner()->GetComponents(OwnersComponents);
	if (OwnersComponents.Num() > 0) {
		for (int32 CompIdx = 0; CompIdx < OwnersComponents.Num(); CompIdx++)
		{
			currentComponentBeingChecked = OwnersComponents[CompIdx];

			if (currentComponentBeingChecked->GetName() == "MessageSystemBoxCollision")
			{
				if (currentComponentBeingChecked != BoxComponent)
				{
					currentComponentBeingChecked->DestroyComponent();
					UE_LOG(LogTemp, Warning, TEXT("MessageSystem BOX Component has been destroyed successfully."));
				}
			}
		}
	}

	BoxComponent->AttachTo(GetOwner()->GetRootComponent());
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));
	BoxComponent->SetRelativeRotation(FRotator(0, 0, 0));
	BoxComponent->SetRelativeScale3D(FVector(0, 0, 0));

	// Add a unique tag in case we want to find if it has a Message System component.
	GetOwner()->Tags.AddUnique(MessageSystemComponent_TagName);

	/////////////////////////////////////////////////////////////
	// PROFESION SYSTEM
	/////////////////////////////////////////////////////////////

/* DEBUG
	FString debugName = GetOwner()->GetName();
	FString debugProfession = UEnum::GetValueAsString(OwnersProfesion.GetValue());
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s has profession: %s"), *debugName, *debugProfession);
*/
}

// Called when the component is going to be destroyed, used for clean up on the owner actor.
void UAC_MessageSystem_Cpp::EndPlay(EEndPlayReason::Type Reason)
{
	if (BoxComponent != nullptr)
	{
		BoxComponent->DestroyComponent();
		BoxComponent->SetActive(false);
		UE_LOG(LogTemp, Warning, TEXT("MessageSystem Component has been destroyed."));
	}

	GetOwner()->Tags.Remove(MessageSystemComponent_TagName);
}

// Called every frame
void UAC_MessageSystem_Cpp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_MessageSystem_Cpp::SendMSG(int32 Receiver, int32 msg, float Delay)
{
	if (MessageManagerAssigned != nullptr)
	{
		//Assemble the new message
		FMessageInfo newMessage;

		newMessage.DispatchTime = Delay;
		newMessage.Sender = actorID;
		newMessage.Receiver = Receiver;
		newMessage.Msg = msg;

		// Send the new message to the Manager to handle it as required
		MessageManagerAssigned->ManageNewMSG(newMessage);
	}
}

void UAC_MessageSystem_Cpp::ReceiveMSG_Implementation(FMessageInfo newMessage)
{


}
