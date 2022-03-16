// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "MessageInfo.h"
#include "MessageManager_C.generated.h"

UCLASS()
class ELARIA_API AMessageManager_C : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMessageManager_C();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 RegisterActor(AActor* actorToRegister, UActorComponent* MessageSystem_Component);

	AActor* GetActorFromID(int32 ID_to_search);

	UActorComponent* GetMessageComponentFromID(int32 ID_to_search);

	int32 GetIDFromActor(AActor* Actor_to_search);

	void ManageNewMSG(FMessageInfo newMessage);

protected:
	// ID / Actor registered
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, AActor*> RegisteredActors;

	UPROPERTY(BlueprintReadOnly)
	TMap<int32, UActorComponent*> RegisteredActors_MessageComponents;

	// Messages pending to be release, based on the Delay time of the msg.
	//TMap<FDateTime, FMessageInfo> DelayedMessages;
	TSortedMap<FDateTime, FMessageInfo> DelayedMessages;

	int32 next_ID_to_assign = 0;
};
