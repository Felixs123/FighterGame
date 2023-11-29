// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FighterGameGameMode.generated.h"

UCLASS(minimalapi)
class AFighterGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFighterGameGameMode();
   virtual void BeginPlay() override;
   void Spawn();
};



