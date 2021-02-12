// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameDev1AssGameModeBase.h"

void AGameDev1AssGameModeBase::BeginPlay() {
	Super::BeginPlay();
	StartGame();
}

void AGameDev1AssGameModeBase::PlayerPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("PlayerPointScored"));
	playerTeamScore++;
	if (playerTeamScore < scoreLimit) RoundReset();
	else GameOver();
}

void AGameDev1AssGameModeBase::EnemyPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("EnemyPointScored"));
	enemyTeamScore++;
	if (enemyTeamScore < scoreLimit) RoundReset();
	else GameOver();
}

void AGameDev1AssGameModeBase::DeleteBall() {
	UE_LOG(LogTemp, Warning, TEXT("DeleteBallCalled "));
	if (inPlayBall) {
		UE_LOG(LogTemp, Warning, TEXT("DeleteBallCalled inPlayBallNotNull"));
		inPlayBall->Destroy();
		inPlayBall = nullptr;
	}
}


void AGameDev1AssGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("StartGameCalled"));
}

void AGameDev1AssGameModeBase::RoundReset() {
	UE_LOG(LogTemp, Warning, TEXT("RoundResetCalled"));
}

void AGameDev1AssGameModeBase::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOverCalled"));
}
