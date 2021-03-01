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

	//Records spawn location to give to GameMode upon death for respawning.
	UFUNCTION() void SetSpawnLocationActor(AActor* SpawnLocationActor);

	//Deletes Ball and possesses it.
	UFUNCTION() void PickUpBall();

	//Returns Ball Held to allow Enemy to head to Player goal and score.
	UFUNCTION() bool BallHeld();

private:

	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//Spawns ball pointed down upon death and notifys.
	void BallDropped();

	UPROPERTY(EditAnywhere) float Health = 100.0f;			   //Adjustable monitor of health of Enemy to track when to die.
	UPROPERTY(EditAnywhere)
		int GunClipSize = 16;								   //Adjustable amount of ammo for Enemy to fire. Not Hooked Up!
	UPROPERTY()
		int GunClipAmmo = 16;								   //Tracker of Enemy ammo spent. Not Hooked Up!
	UPROPERTY() AActor* SpawnLocation;						   //Sent to GameMode upon death so respawn is in same place.
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;	   //Reference to Ball to create Ball upon death.
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;				   //Used to provide reference to GameMode of Ball upon creation.
	UPROPERTY() 
		bool bBallHeld = false;								   //Tracks if Ball is held to allow it to head to Player goal and score.
};
