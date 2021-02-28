// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "GameFramework/Character.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.generated.h"

class AGameDev1AssGameModeBase;

UCLASS()
class GAMEDEV1ASS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void SetSpawnLocationActor(AActor* SpawnLocationActor);
	UFUNCTION() void PickUpBall();
	UFUNCTION() bool BallHeld();

private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void BallDropped();

	UPROPERTY(EditAnywhere) float health = 100.0f;
	UPROPERTY(EditAnywhere)
		int gunClipSize = 16;
	UPROPERTY()
		int gunClipAmmo = 16;
	UPROPERTY() AActor* SpawnLocation;
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;
	UPROPERTY() 
		bool bBallHeld = false;


	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
