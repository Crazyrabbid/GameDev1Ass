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
	virtual void BeginPlay() override; 
	UFUNCTION() void SpawnBasedOnVictory();

private:
	UFUNCTION()
		void TimeUp();
	UPROPERTY()
		FTimerHandle GameOverTimer;
	UPROPERTY()
		bool bVictory = false;
	UPROPERTY(EditAnywhere)
		float GameOverDuration = 30.0f;

	UPROPERTY() TArray<AActor*> Targets;
	UPROPERTY() AActor* PlayerWinSpawn;
	UPROPERTY() AActor* PlayerLossSpawn;
	UPROPERTY() TArray<AActor*> EnemyWinSpawns;
	UPROPERTY() TArray<AActor*> EnemyLossSpawns;

	UPROPERTY(EditAnywhere) TSubclassOf <AEnemyCharacter> EnemyClass;
	UPROPERTY(EditAnywhere) TSubclassOf <APlayerCharacter> PlayerClass;
	UPROPERTY() ACustomPlayerController* PlayerControllerRef;
	UPROPERTY(EditAnywhere) float BackgroundMusicVolume = 1.0f;
	UPROPERTY(EditAnywhere) USoundBase* GameBackgroundMusic;
};
