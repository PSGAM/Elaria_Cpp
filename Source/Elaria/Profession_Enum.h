// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// List of the available profesions
UENUM(BlueprintType)
enum Profesion_Type {
	None = 0 UMETA(DisplayName = "None"),
	Lumberjack = 1 UMETA(DisplayName = "Lumberjack"),
	Quack = 2 UMETA(DisplayName = "Quack"),

};
