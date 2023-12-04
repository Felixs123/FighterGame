// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BaseEnemy.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FighterGameGameMode.generated.h"


UCLASS(minimalapi)
class AFighterGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
   FTimerHandle SpawnTimerHandle;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf <ABaseEnemy> baseEnemy;
	AFighterGameGameMode();
   virtual void BeginPlay() override;
   void Spawn();
   int32 numOfEnemies; 
};



