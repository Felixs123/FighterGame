// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   // Get a reference to the player pawn
   AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

   if(PlayerPawn)
      {
         // Calculate the direction from the enemy to the player
         FVector DirectionToPlayer
            = PlayerPawn->GetActorLocation() - GetActorLocation();
         DirectionToPlayer.Normalize();

         // Set the enemy's rotation to face the player
         FRotator NewRotation = DirectionToPlayer.Rotation();
         SetActorRotation(NewRotation);

         // Move the enemy towards the player
         UCharacterMovementComponent *MovementComponent
            = GetCharacterMovement();
         if(MovementComponent)
            {
               MovementComponent->AddInputVector(DirectionToPlayer);
            }
      }

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

