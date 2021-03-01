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
		void Fire(); //Either throws Ball or fires gun depending on bBallHeld.
	UFUNCTION()
		void Reload(); //Begins reload process, kickstarting timer and stopping Player from firing.
	UFUNCTION()
		void Catch(); //Detects if Player is within certain range before deleting Ball and giving possession to Player.
	UFUNCTION()
		void Strafe(float axisAmount);
	UFUNCTION()
		void Turn(float axisAmount);
	UFUNCTION()
		void Pitch(float axisAmount);
	UFUNCTION()
		void GravLift(FVector LaunchVelocity, bool bXYOverride, bool bZOverride); //Uses CharacterMovementComponent's alternative to forces to allow for a lift.
	UFUNCTION()
		void RecastPlayerCharacter(); //Retrieves Player's new body after death or round restart to control.
	UFUNCTION()
		void ResetHealth(); //Resets health and ammo after death or round restart.

	UPROPERTY()
		APlayerCharacter* PlayerCharacter;		  //Reference to Player's Character to control, move around and delete.
	UPROPERTY()
		ABall* Ball;							  //Reference to Ball to spawn. Pretty sure this is redundant and Player Character handles the Ball spawn instead.

private:
	//UI functions
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

	//Retrieves Overriding bools from Main GameMode.
	UFUNCTION()
		bool GetPlayAllowed();
	UFUNCTION()
		bool GetPlayerDied();

	//Recursive reload function
	UFUNCTION()
		void ReloadTimeUp();	

	//Tells GameMode to begin Respawn timer while dropping any Ball held and finally destroying Player Character.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		float playerHealthMax = 100.0f;					   //Adjustable health that PlayerHealth will adjust to.
	UPROPERTY()											   
		float playerHealth = 100.0f;					   //Monitors health to see when to trigger PlayerDeath.
	UPROPERTY(EditAnywhere)								 
		float moveSpeed = 100.0f;						   //Adjustable multiplier for speed.
	UPROPERTY(EditAnywhere)								
		float rotationSpeed = 200.0f;					   //Adjustable multiplier for speed.
	UPROPERTY(EditAnywhere)								
		float castRange = 10000.0f;						   //Adjustable range of line trace.
	UPROPERTY(EditAnywhere)								
		float impulseForce = 500.0f;					   //Adjustable force of impulse created on gunfire.
	UPROPERTY(EditAnywhere)								
		float ballPickUpDistance = 50.0f;				   //Adjustable range of distance check for pick up.
	UPROPERTY(EditAnywhere)								
		float gunBaseDamage = 20.0f;					   //Adjustable damage to do on gun fire.
	UPROPERTY(EditAnywhere)								
		int gunClipSize = 16;							   //Adjustable ammo amount.
	UPROPERTY()
		int gunClipAmmo = 16;							   //Monitors ammo to see when reload needed and when reload has ended.
	UPROPERTY() 
		bool bBallHeld = false;							   //Monitors if Player has Ball to see when Player shoots if it should throw a Ball instead.
	UPROPERTY() 
		bool bReloading = false;						   //Monitors if Player is reloading to see whether Player can shoot or catch.
	UPROPERTY() FTimerHandle ReloadTimer;							 //Handle for individual bullet reload timer.
	UPROPERTY(EditAnywhere) float ReloadBulletDuration = 0.4f;		 //Adjustable time it takes to reload one bullet.

	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;			   //Reference to GameMode to notify if ball held and to grab overriding Bools.
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;		   //Blueprint to create and attach to viewport.
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> OutOfAmmoClass;									  //Blueprint to create and attach to viewport.
	UPROPERTY(EditAnywhere) TSubclassOf<ADamagePointVisualiser> DamagePointClass;	  //Blueprint to create Sphere to notify player of hit whereabouts.
	UPROPERTY()
		UUserWidget* PlayerHUDCount;				//Monitors UI from Inception and is used as an interface to the UI.
	UPROPERTY()
		UUserWidget* OutOfAmmoCount;				//Monitors No Ammo Notice from Inception and is used as an interface to the No Ammo Notice.
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MiniMapClass;						  //Blueprint to create and attach to viewport.
	UPROPERTY(EditAnywhere) USoundBase* ShotSoundEffect;			  //Sound file to play upon GunFire.
	UPROPERTY(EditAnywhere) float ShotSoundVolume = 1.0f;			  //Volume to play GunFire Sound.
	UPROPERTY(EditAnywhere) USoundBase* ReloadSoundEffect;			  //Sound file to play upon Reload.
	UPROPERTY(EditAnywhere) float ReloadSoundVolume = 1.0f;			  //Volume to play Reload Sound.
	UPROPERTY()
		UUserWidget* MiniMapCount;									  //Monitors MiniMap and is used as an Interface to attach to screen.
};