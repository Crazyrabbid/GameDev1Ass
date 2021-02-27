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
	//UPROPERTY(EditAnywhere) UCustomMovementComponent* CustomCharacterMovement;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Fire();

private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere) UCameraComponent* Camera;
	UPROPERTY(EditAnywhere) USceneCaptureComponent2D* MapCapture;
	UPROPERTY(EditAnywhere) USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere) USpringArmComponent* MapArm;
	UPROPERTY(EditAnywhere) USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;
	UPROPERTY() AGameDev1AssGameModeBase* GameModeRef;
 	/*
	void MoveForwards(float axisAmount);
	void JumpCharacter();
	void Strafe(float axisAmount);
	void Turn(float axisAmount);
	void Pitch(float axisAmount);
	*/
};
