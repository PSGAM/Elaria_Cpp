// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageManager_C.h"
#include "AC_MessageSystem_Cpp.h"

// Sets default values
AMessageManager_C::AMessageManager_C()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMessageManager_C::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMessageManager_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DelayedMessages.Num() > 0)
	{
		FDateTime _currentTime = FDateTime::Now();

		//for (const TPair<FDateTime, FMessageInfo>& pair : DelayedMessages)
		for (const TPair<FDateTime, FMessageInfo>& pair : DelayedMessages)
		{
			if (pair.Key <= _currentTime)
			{
				UActorComponent* receiverMessageComponent = GetMessageComponentFromID(pair.Value.Receiver);
				if (receiverMessageComponent != nullptr)
				{
					Cast<UAC_MessageSystem_Cpp>(receiverMessageComponent)->ReceiveMSG(pair.Value);
				}

				DelayedMessages.Remove(pair.Key);
			}
			else
			{
				break;
			}
		}
	}

}

int32 AMessageManager_C::RegisterActor(AActor* actorToRegister, UActorComponent* MessageSystem_Component)
{
	RegisteredActors.Add(next_ID_to_assign, actorToRegister);
	RegisteredActors_MessageComponents.Add(next_ID_to_assign, MessageSystem_Component);

	next_ID_to_assign++;

	return next_ID_to_assign - 1;
}

AActor* AMessageManager_C::GetActorFromID(int32 ID_to_search)
{
	for (const TPair<int32, AActor*>& pair : RegisteredActors)
	{
		if (pair.Key == ID_to_search)
		{
			return pair.Value;
		}
	}

	// Didn't found the Actor
	return nullptr;
}

UActorComponent* AMessageManager_C::GetMessageComponentFromID(int32 ID_to_search)
{
	for (const TPair<int32, UActorComponent*>& pair : RegisteredActors_MessageComponents)
	{
		if (pair.Key == ID_to_search)
		{
			return pair.Value;
		}
	}

	// Didn't found the Message system component
	return nullptr;
}


int32 AMessageManager_C::GetIDFromActor(AActor* Actor_to_search)
{
	for (const TPair<int32, AActor*>& pair : RegisteredActors)
	{
		if (pair.Value == Actor_to_search)
		{
			return pair.Key;
		}
	}

	// Didn't found the ID
	return -1;
}

void AMessageManager_C::ManageNewMSG(FMessageInfo newMessage)
{
	if (newMessage.DispatchTime <= 0)
	{
		UActorComponent* receiverMessageComponent = GetMessageComponentFromID(newMessage.Receiver);
		if (receiverMessageComponent != nullptr)
		{
			Cast<UAC_MessageSystem_Cpp>(receiverMessageComponent)->ReceiveMSG(newMessage);
		}
	}
	else
	{

		float _tempSeconds = (int)newMessage.DispatchTime % 60;
		float _tempMinutes = (int)newMessage.DispatchTime / 60;

		//FDateTime _tempTimes = FDateTime::Now() + FTimespan::FromSeconds(newMessage.DispatchTime);
		FDateTime _tempTimes = FDateTime::Now() + FTimespan::FromMinutes(_tempMinutes) + FTimespan::FromSeconds(_tempSeconds) + FTimespan::FromMilliseconds(FMath::FRandRange(0, 99));

		/*
		// DEBUG:
				FDateTime CurrentDateTime = FDateTime::Now();
				UE_LOG(LogTemp, Warning, TEXT("Message Delayed: %f minutes and %f seconds. From now (%s) resulting in: %s"), _tempMinutes, _tempSeconds, *CurrentDateTime.ToString(), *_tempTimes.ToString());

		*/
		// New entry will be automatically sorted by the variable type: TSortedMap
		DelayedMessages.Add(_tempTimes, newMessage);

	}
}
