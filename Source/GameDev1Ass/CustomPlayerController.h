// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "CustomPlayerController.generated.h"


/**
 * 
 */

class APlayerCharacter;

UCLASS()
class GAMEDEV1ASS_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent();
	void MoveForwards(float axisAmount);
	void JumpCharacter();
	void Fire();
	void Strafe(float axisAmount);
	void Turn(float axisAmount);
	void Pitch(float axisAmount);

	APlayerCharacter* playerCharacter;

private:
	UPROPERTY(EditAnywhere)
		float moveSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 500.0f;
};
