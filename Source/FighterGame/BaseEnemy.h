// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class FIGHTERGAME_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
   int health; 
	// Sets default values for this character's properties
	ABaseEnemy();
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
   class USphereComponent *AttackRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
