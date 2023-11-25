// Copyright Epic Games, Inc. All Rights Reserved.

#include "FighterGameGameMode.h"
#include "FighterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFighterGameGameMode::AFighterGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
