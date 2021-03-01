// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneCaptureComponent2D;
class AGameDev1AssGameModeBase;

UCLASS()
class GAMEDEV1ASS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


protected:


public:	
	void Fire();				//Spawns a Ball and informs GameMode of Ball creation.
	void BallDropped();			//Spawns a ball pointed down up death.

private:
	//Sends damage notification through to controller to handle.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere) UCameraComponent* Camera;					 //Camera used as main viewpoint for player.
	UPROPERTY(EditAnywhere) USceneCaptureComponent2D* MapCapture;		 //Camera used as orthographic mini map for player to see.
	UPROPERTY(EditAnywhere) USpringArmComponent* SpringArm;				 //Spring arm to regulate and distance Main camera for a consistant experience.
	UPROPERTY(EditAnywhere) USpringArmComponent* MapArm;				 //Spring arm to regulate and distance mini map camera for a consistant experience.
	UPROPERTY(EditAnywhere) USceneComponent* ProjectileSpawnPoint;		 //Used to store relative location to spawn and fire ball from.
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;				 //Blueprint used as a template to create Ball.
	UPROPERTY() AGameDev1AssGameModeBase* GameModeRef;					 //Used to inform GameMode of Damage Taken.
};
