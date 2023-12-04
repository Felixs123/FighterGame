// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FighterGameGameMode.h"
#include "FighterGameCharacter.h"
// Sets default values
ABaseEnemy::ABaseEnemy()
{
   // Set this character to call Tick() every frame.  You can turn this off to
   // improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   MyGameMode = Cast<AFighterGameGameMode>(UGameplayStatics::GetGameMode(this));
   CurrentState = EEnemyState::Patrol; 
   attackRadius = 75;
   MyGameMode = Cast<AFighterGameGameMode>(UGameplayStatics::GetGameMode(this));
   damage = 1; 
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

          if(DistanceToPlayer <= attackRadius)
            {
               // Transition to the Attack state
               CurrentState = EEnemyState::Attack;
            }

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
        
      }
}

void
ABaseEnemy::AttackPlayer()
{
   AActor *PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
   FVector DirectionToPlayer
      = PlayerPawn->GetActorLocation() - GetActorLocation();
   float DistanceToPlayer = DirectionToPlayer.Size();

   if(DistanceToPlayer >= attackRadius)
      {
         CurrentState = EEnemyState::Patrol;
         return;
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
   //UE_LOG(LogTemp, Warning, TEXT("From Base Enemies: %d"), MyGameMode->numOfEnemies);
}

// Called every frame
void
ABaseEnemy::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   switch(CurrentState)
   {
      case EEnemyState::Patrol:
         Patrol();
         break;
      case EEnemyState::Attack:
         //case is in blueprint
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

void
ABaseEnemy::NotifyHit(class UPrimitiveComponent *MyComp, AActor *Other, class UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
   
   Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation,
                    HitNormal, NormalImpulse, Hit);
   UE_LOG(LogTemp, Warning, TEXT("attacked"));
   // Check if the other actor is the player character
   AFighterGameCharacter* PlayerCharacter = Cast<AFighterGameCharacter>(Other);
   if(PlayerCharacter)
   {
         // Call TakeDamage on the player character
         PlayerCharacter->LoseLife(damage);

         // Implement additional logic here, e.g., enemy behavior after
         // hitting the player
   }
}

void
ABaseEnemy::OnHitDone()
{
   // Implement additional logic here, e.g., enemy behavior after hitting the
   // player
   UE_LOG(LogTemp, Warning,TEXT("Hit is done! Additional logic can be executed now."));
}