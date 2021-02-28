// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DamagePointVisualiser.h"
#include "PlayerCharacter.h"
#include "CustomPlayerController.generated.h"

class AGameDev1AssGameModeBase;

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
	UFUNCTION()
		void MoveForwards(float axisAmount);
	UFUNCTION()
		void JumpCharacter();
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void Reload();
	UFUNCTION()
		void Catch();
	UFUNCTION()
		void Strafe(float axisAmount);
	UFUNCTION()
		void Turn(float axisAmount);
	UFUNCTION()
		void Pitch(float axisAmount);
	UFUNCTION()
		void GravLift(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);
	UFUNCTION()
		void RecastPlayerCharacter();
	UFUNCTION()
		void ResetHealth();

	UPROPERTY()
		APlayerCharacter* playerCharacter;
	UPROPERTY()
		ABall* ball;

private:
	UFUNCTION(BlueprintPure)
		float GetHealth();
	UFUNCTION(BlueprintPure)
		float GetHealthTotal();
	UFUNCTION(BlueprintPure)
		float GetAmmo();
	UFUNCTION(BlueprintPure)
		float GetAmmoTotal();
	UFUNCTION(BlueprintPure)
		FString GetItemEquiped();
	UFUNCTION()
		bool GetPlayAllowed();
	UFUNCTION()
		bool GetPlayerDied();

	UFUNCTION()
		void ReloadTimeUp();	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		float playerHealthMax = 100.0f;
	UPROPERTY()
		float playerHealth = 100.0f;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 200.0f;
	UPROPERTY(EditAnywhere)
		float castRange = 10000.0f;
	UPROPERTY(EditAnywhere)
		float impulseForce = 500.0f;
	UPROPERTY(EditAnywhere)
		float ballPickUpDistance = 50.0f;
	UPROPERTY(EditAnywhere)
		float gunBaseDamage = 20.0f;
	UPROPERTY(EditAnywhere)
		int gunClipSize = 16;
	UPROPERTY()
		int gunClipAmmo = 16;
	UPROPERTY() //Swap this for vs only after testing
		bool bBallHeld = false;
	UPROPERTY() //Swap this for vs only after testing
		bool bReloading = false;
	UPROPERTY() FTimerHandle ReloadTimer;
	UPROPERTY(EditAnywhere) float ReloadBulletDuration = 0.4f;

	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> OutOfAmmoClass;
	UPROPERTY(EditAnywhere) TSubclassOf<ADamagePointVisualiser> DamagePointClass;
	UPROPERTY()
		UUserWidget* PlayerHUDCount;
	UPROPERTY()
		UUserWidget* OutOfAmmoCount;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MiniMapClass;
	UPROPERTY(EditAnywhere) USoundBase* ShotSoundEffect;
	UPROPERTY(EditAnywhere) float ShotSoundVolume = 1.0f;
	UPROPERTY(EditAnywhere) USoundBase* ReloadSoundEffect;
	UPROPERTY(EditAnywhere) float ReloadSoundVolume = 1.0f;
	UPROPERTY()
		UUserWidget* MiniMapCount;
};