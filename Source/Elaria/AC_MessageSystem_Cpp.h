// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "MessageManager_C.h"
#include "AC_MessageSystem_Cpp.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class ELARIA_API UAC_MessageSystem_Cpp : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceiveMSG_Signature, FMessageInfo, newMessage);

public:	
	// Sets default values for this component's properties
	UAC_MessageSystem_Cpp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void SendMSG(int32 Receiver, int32 msg, float Delay);

	//UFUNCTION(BlueprintNativeEvent)
	UFUNCTION()
	void ReceiveMSG(FMessageInfo newMessage);


public:
	UPROPERTY(BlueprintReadOnly, Category = "MessageSystem")
	AMessageManager_C* MessageManagerAssigned;

	// The ID used by the message system to identify a specific actor
	UPROPERTY(BlueprintReadOnly, Category = "MessageSystem")
	int32 actorID = -1;

	const FName MessageSystemComponent_TagName = "MessageSystemComponent_Tag";

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "MSG_Received"))
	FReceiveMSG_Signature ReceiveMSG_Delegate;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

};
