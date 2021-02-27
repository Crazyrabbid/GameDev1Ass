// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameDev1AssGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"


void AGameDev1AssGameModeBase::BeginPlay() {
	Super::BeginPlay();
	StartGame();
}

void AGameDev1AssGameModeBase::PlayerPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("PlayerPointScored"));
	playerTeamScore++;
	BlueTeamScoredCount = CreateWidget(GetWorld(), BlueTeamScoredClass);
	if (BlueTeamScoredCount) BlueTeamScoredCount->AddToViewport();
	if (playerTeamScore < scoreLimit) RoundReset();
	else GameOver(true);
}

void AGameDev1AssGameModeBase::EnemyPointScored() {
	UE_LOG(LogTemp, Warning, TEXT("EnemyPointScored"));
	enemyTeamScore++;
	RedTeamScoredCount = CreateWidget(GetWorld(), RedTeamScoredClass);
	if (RedTeamScoredCount) RedTeamScoredCount->AddToViewport();
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

bool AGameDev1AssGameModeBase::GetPlayAllowed()
{
	return bPlayAllowed;
}


void AGameDev1AssGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("StartGameCalled"));
	UGameplayStatics::PlaySound2D(GetWorld(), GameBackgroundMusic, BackgroundMusicVolume, 1.0f, 0.0f);
	PlayerControllerRef = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (BallClass && EnemyClass && PlayerClass) {
		UE_LOG(LogTemp, Warning, TEXT("Ball Class Exist"));
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Targets);
		for (AActor* Waypoint : Targets) {
			if (Waypoint->ActorHasTag(TEXT("BallSpawnPoint"))) { 
				BallSpawn = Waypoint;
			}
			else if (Waypoint->ActorHasTag(TEXT("RedSpawn"))) {
				EnemySpawns.Emplace(Waypoint);
			}
			else if (Waypoint->ActorHasTag(TEXT("PlayerSpawn"))) {
				PlayerSpawn = Waypoint;
			}
		}
		RoundBeginSpawning();
	}
	bPlayAllowed = false;
	GetWorld()->GetTimerManager().SetTimer(RoundBeginningTimer, this, &AGameDev1AssGameModeBase::GameBeginningTimeUp, RoundStartDuration, false);
	WarmUpCountdownCount = CreateWidget(GetWorld(), WarmUpCountdownClass);
	if (WarmUpCountdownCount) WarmUpCountdownCount->AddToViewport();
}

void AGameDev1AssGameModeBase::RoundBeginSpawning()
{
	if (BallSpawn) {
		FVector SpawnLocation = BallSpawn->GetActorLocation();
		FRotator SpawnRotation = FRotator(90.0f,0.0f,0.0f);
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
		TempBall->SetOwner(this);
		inPlayBall = TempBall;
	}
	
	if (EnemySpawns.Num() != 0) {
		for (AActor* SpawnPoint : EnemySpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation);
		}
	}

	if (PlayerSpawn) {
		FVector SpawnLocation = PlayerSpawn->GetActorLocation();
		FRotator SpawnRotation = PlayerSpawn->GetActorRotation();
		APlayerCharacter* TempPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotation);
		TempPlayer->SetOwner(this);
	}
}

void AGameDev1AssGameModeBase::RoundEndRemovals()
{
	DeleteBall();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), Targets);
	for (AActor* player : Targets) {
		player->Destroy();
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), Targets);
	for (AActor* Enemy : Targets) {
		Enemy->Destroy();
	}
}

void AGameDev1AssGameModeBase::RoundReset() {
	GetWorld()->GetTimerManager().PauseTimer(EndMatchTimer);
	bPlayAllowed = false;
	RoundEndRemovals();
	UE_LOG(LogTemp, Warning, TEXT("RoundResetCalled"));
	RoundBeginSpawning();
	PlayerControllerRef->RecastPlayerCharacter();

	GetWorld()->GetTimerManager().SetTimer(RoundBeginningTimer, this, &AGameDev1AssGameModeBase::RoundBeginningTimeUp, RoundStartDuration, false);
	WarmUpCountdownCount = CreateWidget(GetWorld(), WarmUpCountdownClass);
	if (WarmUpCountdownCount) WarmUpCountdownCount->AddToViewport();
}

void AGameDev1AssGameModeBase::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("TimeUpCalled"));
	bPlayAllowed = false;
	if (playerTeamScore > enemyTeamScore) {
		GameOver(true);

	}
	else{
		GameOver(false);
	}
}

void AGameDev1AssGameModeBase::RoundBeginningTimeUp()
{
	GetWorld()->GetTimerManager().UnPauseTimer(EndMatchTimer);
	bPlayAllowed = true;
	UE_LOG(LogTemp, Warning, TEXT("Play allowed value %s"), bPlayAllowed ? TEXT("true") : TEXT("false"));
}

void AGameDev1AssGameModeBase::GameBeginningTimeUp()
{
	MatchTimerCount = CreateWidget(GetWorld(), MatchTimerClass);
	bPlayAllowed = true;
	if (MatchTimerCount) MatchTimerCount->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(EndMatchTimer, this, &AGameDev1AssGameModeBase::TimeUp, MatchDuration, false);
}

FString AGameDev1AssGameModeBase::GetTime()
{
	int timeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(EndMatchTimer);
	int minsRemaining = timeRemaining / 60;
	int secsRemaining = timeRemaining % 60;
	FString timeDesc = FString::Printf(TEXT("%02d:%02d"), minsRemaining, secsRemaining);
	return timeDesc;
}

float AGameDev1AssGameModeBase::GetBlueScore()
{
	return playerTeamScore;
}

float AGameDev1AssGameModeBase::GetRedScore()
{
	return enemyTeamScore;
}

void AGameDev1AssGameModeBase::GameOver(bool win)
{
	if(GetWorld()->GetTimerManager().TimerExists(EndMatchTimer)) GetWorld()->GetTimerManager().ClearTimer(EndMatchTimer);
	bPlayAllowed = false;
	UE_LOG(LogTemp, Warning, TEXT("GameOverCalled"));
	if (win) {
		UGameplayStatics::OpenLevel(GetWorld(), "EndScreenWin");
	}
	else {
		UGameplayStatics::OpenLevel(GetWorld(), "EndScreenLoss");
	}
}
