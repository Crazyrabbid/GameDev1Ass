// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomPlayerController.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "PlayerCharacter.h"
#include "Ball.h"
#include "GameDev1AssGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API AGameDev1AssGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void PlayerPointScored();
	UFUNCTION()
		void EnemyPointScored();
	UFUNCTION()
		void DeleteBall();
	UFUNCTION()
		bool GetPlayAllowed();
	UFUNCTION()
		bool GetPlayerDead();
	UFUNCTION()
		void BeginPlayerRespawnProcess();
	UFUNCTION()
		void BeginEnemyRespawnProcess(AActor* Spawn);

	UPROPERTY(EditAnywhere)
		ABall* inPlayBall;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void StartGame();
	UFUNCTION()
		void GameOver(bool Win);
	UFUNCTION()
		void RoundReset();
	UFUNCTION()
		void TimeUp();
	UFUNCTION()
		void RoundBeginSpawning();
	UFUNCTION()
		void RoundEndRemovals();
	UFUNCTION()
		void RoundBeginningTimeUp();
	UFUNCTION()
		void GameBeginningTimeUp();
	UFUNCTION()
		void PlayerRespawnTimeUp();
	UFUNCTION()
		void EnemyRespawnTimeUp();
	UFUNCTION(BlueprintPure)
		FString GetTime();
	UFUNCTION(BlueprintPure)
		float GetBlueScore();
	UFUNCTION(BlueprintPure)
		float GetRedScore();


	UPROPERTY(EditAnywhere) int scoreLimit = 3;
	UPROPERTY() int playerTeamScore = 0;
	UPROPERTY() int enemyTeamScore = 0;

	UPROPERTY() TArray<AActor*> Targets;
	UPROPERTY() AActor* BallSpawn;
	UPROPERTY() AActor* PlayerSpawn;
	UPROPERTY() TArray<AActor*> TempEnemySpawns;
	UPROPERTY() TArray<AActor*> EnemySpawns;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> BlueTeamScoredClass;
	UPROPERTY() UUserWidget* BlueTeamScoredCount;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> RedTeamScoredClass;
	UPROPERTY() UUserWidget* RedTeamScoredCount;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> WarmUpCountdownClass;
	UPROPERTY() UUserWidget* WarmUpCountdownCount;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> MatchTimerClass;
	UPROPERTY() UUserWidget* MatchTimerCount;


	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;
	UPROPERTY(EditAnywhere) TSubclassOf <AEnemyCharacter> EnemyClass;
	UPROPERTY(EditAnywhere) TSubclassOf <APlayerCharacter> PlayerClass;
	UPROPERTY(EditAnywhere) USoundBase* GameBackgroundMusic;
	UPROPERTY(EditAnywhere) float BackgroundMusicVolume = 1.0f;
	UPROPERTY() AEnemyAIController* EnemyAIControllerRef;
	UPROPERTY() ACustomPlayerController* PlayerControllerRef;


	UPROPERTY() FTimerHandle EndMatchTimer;
	UPROPERTY(EditAnywhere) float MatchDuration = 300.0f;
	UPROPERTY() FTimerHandle RoundBeginningTimer;
	UPROPERTY(EditAnywhere) float RoundStartDuration = 4.0f;
	UPROPERTY() FTimerHandle PlayerRespawnTimer;
	UPROPERTY(EditAnywhere) float PlayerRespawnDuration = 3.0f;
	UPROPERTY() FTimerHandle EnemyRespawnTimer;
	UPROPERTY(EditAnywhere) float EnemyRespawnDuration = 3.0f;

	UPROPERTY() bool bPlayAllowed = false;
	UPROPERTY() bool bPlayerDead = false;

};
