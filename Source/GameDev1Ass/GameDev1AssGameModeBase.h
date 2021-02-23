// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
		void RoundBeginningTimeUp();
	UFUNCTION()
		void GameBeginningTimeUp();
	UFUNCTION(BlueprintPure)
		FString GetTime();
	UFUNCTION(BlueprintPure)
		float GetBlueScore();
	UFUNCTION(BlueprintPure)
		float GetRedScore();

	UPROPERTY(EditAnywhere) //Don't Expose after testing
		int playerTeamScore = 0;
	UPROPERTY(EditAnywhere) //Don't Expose after testing
		int enemyTeamScore = 0;
	UPROPERTY(EditAnywhere)
		int scoreLimit = 3;
	UPROPERTY()
		TArray<AActor*> Targets;
	UPROPERTY()
		AActor* BallSpawn;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> BlueTeamScoredClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> RedTeamScoredClass;
	UPROPERTY()
		UUserWidget* RedTeamScoredCount;
	UPROPERTY()
		UUserWidget* BlueTeamScoredCount;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> WarmUpCountdownClass;
	UPROPERTY()
		UUserWidget* WarmUpCountdownCount;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> MatchTimerClass;
	UPROPERTY()
		UUserWidget* MatchTimerCount;
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;
	UPROPERTY()
		FTimerHandle EndMatchTimer;
	UPROPERTY(EditAnywhere)
		float MatchDuration = 300.0f;
	UPROPERTY()
		FTimerHandle RoundBeginningTimer;
	UPROPERTY(EditAnywhere)
		float RoundStartDuration = 4.0f;
	UPROPERTY()
		bool bPlayAllowed = false;
};
