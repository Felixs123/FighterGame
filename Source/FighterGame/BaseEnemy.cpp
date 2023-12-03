// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FighterGameGameMode.h"
// Sets default values
ABaseEnemy::ABaseEnemy()
{
   // Set this character to call Tick() every frame.  You can turn this off to
   // improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   CurrentState = EEnemyState::Patrol; 
   attackRadius = 300;
   MyGameMode = Cast<AFighterGameGameMode>(UGameplayStatics::GetGameMode(this));
}

void
ABaseEnemy::Patrol()
{
   // Get a reference to the player pawn
   AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

   if(PlayerPawn)
      {
         // Calculate the direction from the enemy to the player
         FVector DirectionToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
         float DistanceToPlayer = DirectionToPlayer.Size();
         DirectionToPlayer.Normalize();
         // Set the enemy's rotation to face the player
         FRotator NewRotation = DirectionToPlayer.Rotation();
         SetActorRotation(NewRotation);

         // Move the enemy towards the player
         UCharacterMovementComponent *MovementComponent = GetCharacterMovement();
         if(MovementComponent)
         {

               // Set the movement input to move towards the player
               MovementComponent->AddInputVector(DirectionToPlayer);

         }
         else
         {
               UE_LOG(LogTemp, Warning, TEXT("Cry yourself to sleep"));
         }
         //CONDITION TO GO INTO ATTACK
         // Calculate the distance to the player
         
         UE_LOG(LogTemp, Warning, TEXT("Distance %f"), DistanceToPlayer);
         // Check if the enemy is within the attack radius
         if(DistanceToPlayer <=attackRadius)
         {
             // Transition to the Attack state
             CurrentState = EEnemyState::Attack;
         }
      }
}

void
ABaseEnemy::AttackPlayer()
{
   // Get a reference to the player pawn
   AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
   // Calculate the direction from the enemy to the player
   FVector DirectionToPlayer
      = PlayerPawn->GetActorLocation() - GetActorLocation();
   float DistanceToPlayer = DirectionToPlayer.Size();

   UE_LOG(LogTemp, Warning, TEXT("Player Location: %s"),
          *PlayerPawn->GetActorLocation().ToString());
   UE_LOG(LogTemp, Warning, TEXT("Enemy Location: %s"),
          *GetActorLocation().ToString());
   UE_LOG(LogTemp, Warning, TEXT("DirectionToPlayer: %s"),
          *DirectionToPlayer.ToString());
   UE_LOG(LogTemp, Warning, TEXT("Distance %f"), DistanceToPlayer);
   if(DistanceToPlayer >= attackRadius)
      {
         // Transition to the Attack state
         CurrentState = EEnemyState::Patrol;
      }
}

void
ABaseEnemy::Death()
{
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
   //UE_LOG(LogTemp, Warning, TEXT("From Base Enemies: %d"), MyGameMode->numOfEnemies);
}

// Called every frame
void
ABaseEnemy::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   UE_LOG(
      LogTemp, Warning, TEXT("Current State: %d"),
      static_cast<int32>(CurrentState)); // Implement a simple state machine
   switch(CurrentState)
      {
      case EEnemyState::Patrol:
         Patrol();
         break;
      case EEnemyState::Attack:
         AttackPlayer();
         break;
      case EEnemyState::Death:
         Death();
         break;

      default:
         break;
      }
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}