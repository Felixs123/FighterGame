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
<<<<<<< HEAD

=======
   EEnemyState CurrentState;
>>>>>>> 15c1a9191dd200c7079921b4da8131fd24d2e0d7
   int health; 
   int attackRadius; 
	// Sets default values for this character's properties
	ABaseEnemy();

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
   class USphereComponent *AttackRadius;
   class AFighterGameGameMode *MyGameMode;
<<<<<<< HEAD
=======

   void Patrol();
   void AttackPlayer();
   void Death();
>>>>>>> 15c1a9191dd200c7079921b4da8131fd24d2e0d7

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
