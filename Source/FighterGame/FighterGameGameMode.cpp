// Copyright Epic Games, Inc. All Rights Reserved.

#include "FighterGameGameMode.h"
#include "FighterGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "BaseEnemy.h"
#include "FloatingActor.h"


AFighterGameGameMode::AFighterGameGameMode()
{
	 //set default pawn class to our Blueprinted character
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
   GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AFighterGameGameMode::Spawn, 5.0f, true);
}

void
AFighterGameGameMode::Spawn()
{
   UE_LOG(LogTemp, Warning, TEXT("Hello"));

   if(baseEnemy)
   {
      // Get a reference to the player pawn
      AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

      // Handle the case where the player pawn is not found
      if(!PlayerPawn)
         {
            return;
         }

      FVector SpawnLocation;
      FCollisionQueryParams CollisionParams;

      do
         {
            UE_LOG(LogTemp, Warning, TEXT("Creature not spawned"));

            // Define the spawn radius around the player
            float SpawnRadius = 500.0f;

            // Calculate a random spawn location within the radius
            FVector2D SpawnLocation2D = FMath::RandPointInCircle(SpawnRadius);
            SpawnLocation
               = FVector(SpawnLocation2D.X, SpawnLocation2D.Y, 0.0f)
                 + PlayerPawn->GetActorLocation();

            // Initialize HitResult
            FHitResult HitResult;

            // Find the floor at the spawn location
            if(GetWorld()->SweepSingleByChannel(
                  HitResult, SpawnLocation,
                  SpawnLocation - FVector(0, 0, 1000), FQuat::Identity,
                  ECC_Visibility, FCollisionShape::MakeSphere(50),
                  CollisionParams))
               {
                  // Set the spawn location to the floor location
                  SpawnLocation.Z
                     = HitResult.ImpactPoint.Z + 50.0f; // Adjust as needed
               }

            // Check if colliding
            CollisionParams.AddIgnoredActor(PlayerPawn);
         }
      while(GetWorld()->LineTraceTestByChannel(PlayerPawn->GetActorLocation(),
                                               SpawnLocation, ECC_Visibility,
                                               CollisionParams));

      if(!GetWorld()->LineTraceTestByChannel(PlayerPawn->GetActorLocation(),
                                             SpawnLocation, ECC_Visibility,
                                             CollisionParams))
         {
            // Spawn the creature
            ABaseEnemy *NewCreature = GetWorld()->SpawnActor<ABaseEnemy>(
               baseEnemy, SpawnLocation, FRotator::ZeroRotator);
            UE_LOG(LogTemp, Warning,
                   TEXT("Creature spawned at X: %f, Y: %f, Z: %f"),
                   SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
         }
      else
         {
            UE_LOG(LogTemp, Warning, TEXT("Creature not spawned"));
         }
   }
}

