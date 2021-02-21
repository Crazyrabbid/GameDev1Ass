// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GameDev1AssGameModeBase.h"
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
	void Catch();
	void Strafe(float axisAmount);
	void Turn(float axisAmount);
	void Pitch(float axisAmount);

	APlayerCharacter* playerCharacter;
	ABall* ball;

private:
	UFUNCTION(BlueprintPure)
		float GetHealth();
	UFUNCTION(BlueprintPure)
		float GetHealthTotal();

	UPROPERTY(EditAnywhere)
		float playerHealthMax = 100.0f;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 500.0f;
	UPROPERTY(EditAnywhere)
		float castRange = 10000.0f;
	UPROPERTY(EditAnywhere)
		float impulseForce = 500.0f;
	UPROPERTY(EditAnywhere) //Swap this for vs only after testing
		bool ballHeld = false;

	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY()
		UUserWidget* PlayerHUDCount;
	UPROPERTY()
		float playerHealth = 100.0f;
};
