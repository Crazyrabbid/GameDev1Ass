// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AEndLevelGameMode::BeginPlay() {
	Super::BeginPlay();

	//Recieves Player and Enemy positions to spawn and Begins screen timer.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Targets);
	for (AActor* Waypoint : Targets) {
		if (Waypoint->ActorHasTag(TEXT("PlayerWinSpawn"))) {
			PlayerWinSpawn = Waypoint;
		}
		else if (Waypoint->ActorHasTag(TEXT("PlayerLossSpawn"))) {
			PlayerLossSpawn = Waypoint;
		}
		else if (Waypoint->ActorHasTag(TEXT("EnemyWinSpawn"))) {
			EnemyWinSpawns.Emplace(Waypoint);
		}
		else if (Waypoint->ActorHasTag(TEXT("EnemyLossSpawn"))) {
			EnemyLossSpawns.Emplace(Waypoint);
		}
	}

	SpawnBasedOnVictory();

	UGameplayStatics::PlaySound2D(GetWorld(), GameBackgroundMusic, BackgroundMusicVolume, 1.0f, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(GameOverTimer, this, &AEndLevelGameMode::TimeUp, GameOverDuration, false);
}

void AEndLevelGameMode::SpawnBasedOnVictory()
{
	//Spawns Player or Enemy in each position depending on tag.
	if (GetWorld()->GetName() == (TEXT("EndScreenWin"))) {
		if (PlayerWinSpawn) {
			FVector SpawnLocation = PlayerWinSpawn->GetActorLocation();
			FRotator SpawnRotation = PlayerWinSpawn->GetActorRotation();
			APlayerCharacter* TempPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotation);
		}

		if (EnemyLossSpawns.Num() != 0) {
			for (AActor* SpawnPoint : EnemyLossSpawns) {
				FVector SpawnLocation = SpawnPoint->GetActorLocation();
				FRotator SpawnRotation = SpawnPoint->GetActorRotation();
				AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation);
			}
		}
	}
	else {
		if (PlayerLossSpawn) {
			FVector SpawnLocation = PlayerLossSpawn->GetActorLocation();
			FRotator SpawnRotation = PlayerLossSpawn->GetActorRotation();
			APlayerCharacter* TempPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotation);
		}

		if (EnemyWinSpawns.Num() != 0) {
			for (AActor* SpawnPoint : EnemyWinSpawns) {
				FVector SpawnLocation = SpawnPoint->GetActorLocation();
				FRotator SpawnRotation = SpawnPoint->GetActorRotation();
				AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation);
			}
		}
	}
}

void AEndLevelGameMode::TimeUp()
{
	//Switches screen to main menu.
	UE_LOG(LogTemp, Warning, TEXT("TimeUpCalled"));
	if (GetWorld()->GetTimerManager().TimerExists(GameOverTimer)) GetWorld()->GetTimerManager().ClearTimer(GameOverTimer);
	UGameplayStatics::OpenLevel(GetWorld(), "StartMenu");
}