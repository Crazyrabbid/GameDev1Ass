// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameDev1AssGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"


void AGameDev1AssGameModeBase::BeginPlay() {
	Super::BeginPlay();
	StartGame();
}

void AGameDev1AssGameModeBase::PlayerPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("PlayerPointScored"));
	playerTeamScore++;
	if (playerTeamScore < scoreLimit) RoundReset();
	else GameOver(true);
}

void AGameDev1AssGameModeBase::EnemyPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("EnemyPointScored"));
	enemyTeamScore++;
	if (enemyTeamScore < scoreLimit) RoundReset();
	else GameOver(false);
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
	if (BallClass) {
		UE_LOG(LogTemp, Warning, TEXT("Ball Class Exist"));
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Targets);
		for (AActor* Waypoint : Targets) {
			if (Waypoint->ActorHasTag(TEXT("BallSpawnPoint"))) { 
				BallSpawn = Waypoint;
				FVector SpawnLocation = BallSpawn->GetActorLocation();
				FRotator SpawnRotation = FRotator(90.0f,0.0f,0.0f);
				ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
				TempBall->SetOwner(this);
				UE_LOG(LogTemp, Warning, TEXT("inPlayBall Assigned"));
				inPlayBall = TempBall;
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(EndMatchTimer, this, &AGameDev1AssGameModeBase::TimeUp, MatchDuration, false);
}

void AGameDev1AssGameModeBase::RoundReset() {
	UE_LOG(LogTemp, Warning, TEXT("RoundResetCalled"));
}

void AGameDev1AssGameModeBase::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("TimeUpCalled"));
	GameOver(false);
}

void AGameDev1AssGameModeBase::GameOver(bool win)
{
	UE_LOG(LogTemp, Warning, TEXT("GameOverCalled"));
	UGameplayStatics::OpenLevel(GetWorld(), "EndScreen");
}
