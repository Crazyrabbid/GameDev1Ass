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

	UPROPERTY(EditAnywhere)
		ABall* inPlayBall;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void StartGame();
	UFUNCTION()
		void GameOver();

	UPROPERTY(EditAnywhere) //Don't Expose after testing
		int playerTeamScore = 0;
	UPROPERTY(EditAnywhere) //Don't Expose after testing
		int enemyTeamScore = 0;
	UPROPERTY(EditAnywhere)
		int scoreLimit = 3;

};
