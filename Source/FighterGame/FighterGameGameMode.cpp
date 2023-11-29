// Copyright Epic Games, Inc. All Rights Reserved.

#include "FighterGameGameMode.h"
#include "FighterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "BaseEnemy.h"
#include "FloatingActor.h"


AFighterGameGameMode::AFighterGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	UE_LOG(LogTemp, Warning, TEXT("Hello")); 
    
}

void
AFighterGameGameMode::BeginPlay()
{
   Spawn();
}

void
AFighterGameGameMode::Spawn()
{
   // Get a reference to the player pawn
   AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    // Handle the case where the player pawn is not found
   if(!PlayerPawn)
   {
      return;
   }

   // Define the spawn radius around the player
   float SpawnRadius = 100.0f;

   // Calculate a random spawn location within the radius
   FVector2d SpawnLocation2D = FMath::RandPointInCircle(SpawnRadius);
   FVector SpawnLocation = FVector(SpawnLocation2D.X, SpawnLocation2D.Y, 100.0f) + PlayerPawn->GetActorLocation();

   //Check if colliding
   FCollisionQueryParams CollisionParams;
   CollisionParams.AddIgnoredActor(PlayerPawn);

   //if(!GetWorld()->LineTraceTestByChannel(PlayerPawn->GetActorLocation(), SpawnLocation, ECC_Visibility, CollisionParams))
   //{
      // Spawn the creature
       
      ABaseEnemy *NewCreature = GetWorld()->SpawnActor<ABaseEnemy>(ABaseEnemy::StaticClass(), SpawnLocation, FRotator::ZeroRotator);
      UE_LOG(LogTemp, Warning, TEXT("Creature spawned at X: %f, Y: %f, Z: %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z); 

   //}
}
