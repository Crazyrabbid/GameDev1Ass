// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyCharacter.h"
#include "CustomPlayerController.h"
#include "PlayerCharacter.h"
#include "EndLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API AEndLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override; 					//Recieves Player and Enemy positions to spawn and Begins screen timer.
	UFUNCTION() void SpawnBasedOnVictory();				//Spawns Player or Enemy in each position depending on tag.

private:
	UFUNCTION()
		void TimeUp();									//Switches screen to main menu.
	UPROPERTY()
		FTimerHandle GameOverTimer;						//Handle to edit, add and remove main menu transition timer.
	UPROPERTY()
		bool bVictory = false;							//Bool to detect which positions to spawn player. Has been made redundant.
	UPROPERTY(EditAnywhere)
		float GameOverDuration = 30.0f;					//Length of time before Main Menu switch.

	UPROPERTY() TArray<AActor*> Targets;				//Holds all TargetPoints within level to sort through for tags.
	UPROPERTY() AActor* PlayerWinSpawn;					//Holds position and rotation to spawn Player if won.
	UPROPERTY() AActor* PlayerLossSpawn;				//Holds position and rotation to spawn Player if lost.
	UPROPERTY() TArray<AActor*> EnemyWinSpawns;			//Holds position and rotation to spawn Enemy if won.
	UPROPERTY() TArray<AActor*> EnemyLossSpawns;		//Holds position and rotation to spawn Enemy if lost.

	UPROPERTY(EditAnywhere) TSubclassOf <AEnemyCharacter> EnemyClass;	   //Blueprint of Enemy to use as a template to spawn.
	UPROPERTY(EditAnywhere) TSubclassOf <APlayerCharacter> PlayerClass;	   //Blueprint of Player to use as a template to spawn.
	UPROPERTY() ACustomPlayerController* PlayerControllerRef;			   //Reference of PlayerController to tell PlayerController to regrab Player Character.
	UPROPERTY(EditAnywhere) float BackgroundMusicVolume = 1.0f;			   //Volume to play Background music.
	UPROPERTY(EditAnywhere) USoundBase* GameBackgroundMusic;			   //Background music to play.
};
