// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "AC_PointOfInterest_C.generated.h"

UENUM(BlueprintType)
enum PointOfInterest_Type {
	POI_None = 0 UMETA(DisplayName = "None"),
	POI_Tree = 1 UMETA(DisplayName = "POI_Tree"),
	POI_Log = 2 UMETA(DisplayName = "POI_Log"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class ELARIA_API UAC_PointOfInterest_C : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_PointOfInterest_C();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void POI_DeactivateCollision();

	UFUNCTION(BlueprintCallable)
	void POI_ActivateCollision();

	UFUNCTION(BlueprintCallable)
	PointOfInterest_Type GetPOIType();

public:	
	const FName PointOfInterestComponent_TagName = "PointOfInterestComponent_Tag";

	UPROPERTY(EditAnywhere, Category = "PointOfInterest")
	TEnumAsByte<PointOfInterest_Type> PointOfInterest_Type_enum = PointOfInterest_Type::POI_None;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

	
};
