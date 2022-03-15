// Copyright Epic Games, Inc. All Rights Reserved.

#include "ElariaGameMode.h"
#include "ElariaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AElariaGameMode::AElariaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
