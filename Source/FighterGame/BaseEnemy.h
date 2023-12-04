// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
   Patrol UMETA(DisplayName = "Patrol"),
   Attack UMETA(DisplayName = "Attack"),
   Death UMETA(DisplayName = "Death")
};

UCLASS()
class FIGHTERGAME_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:

   UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
   EEnemyState CurrentState;


   int health;
   int damage;
   int attackRadius; 
	// Sets default values for this character's properties
	ABaseEnemy();

   class AFighterGameGameMode *MyGameMode;


   void Patrol();
   UFUNCTION(BlueprintCallable, Category = "Attack")
   void AttackPlayer();
   void Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
   virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

   void OnHitDone();

   void NotifyHit(UPrimitiveComponent *MyComp, AActor *Other,
                  UPrimitiveComponent *OtherComp, bool bSelfMoved,
                  FVector HitLocation, FVector HitNormal,
                  FVector NormalImpulse, const FHitResult &Hit) override;

};
