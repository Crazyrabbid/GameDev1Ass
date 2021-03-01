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
	//Increases Players score. Spawns UI notice and either resets round or continues to end screen if over score threshold.
	UE_LOG(LogTemp, Warning, TEXT("PlayerPointScored"));
	playerTeamScore++;
	BlueTeamScoredCount = CreateWidget(GetWorld(), BlueTeamScoredClass);
	if (BlueTeamScoredCount) BlueTeamScoredCount->AddToViewport();
	if (playerTeamScore < scoreLimit) RoundReset();
	else GameOver(true);
}

void AGameDev1AssGameModeBase::EnemyPointScored() {
	//Increases Enemy score. Spawns UI notice and either resets round or continues to end screen if over score threshold.
	UE_LOG(LogTemp, Warning, TEXT("EnemyPointScored"));
	enemyTeamScore++;
	RedTeamScoredCount = CreateWidget(GetWorld(), RedTeamScoredClass);
	if (RedTeamScoredCount) RedTeamScoredCount->AddToViewport();
	if (enemyTeamScore < scoreLimit) RoundReset();
	else GameOver(false);
}

void AGameDev1AssGameModeBase::DeleteBall() {
	//Removes Ball and removes reference to avoid Crash.
	UE_LOG(LogTemp, Warning, TEXT("DeleteBallCalled "));
	if (inPlayBall) {
		UE_LOG(LogTemp, Warning, TEXT("DeleteBallCalled inPlayBallNotNull"));
		inPlayBall->Destroy();
		inPlayBall = nullptr;
	}
}

bool AGameDev1AssGameModeBase::GetPlayAllowed()
{
	//Used to control if Enemy and Player can move or act.
	return bPlayAllowed;
}

bool AGameDev1AssGameModeBase::GetPlayerDead()
{
	//Used to stop Player Controller trying to commit actions while Player is dead.
	return bPlayerDead;
}

bool AGameDev1AssGameModeBase::GetBallHeld()
{
	//Used to stop crash upon Enemy trying to read Ball location when not spawned.
	return bBallHeld;
}

void AGameDev1AssGameModeBase::SetBallHeld(bool BallHeld)
{
	//Allows Enemy or Player to update if they have the Ball.
	bBallHeld = BallHeld;
}

void AGameDev1AssGameModeBase::BeginPlayerRespawnProcess()
{
	//Begins timer for Player respawn and initiates visual countdown.
	bPlayerDead = true;
	GetWorld()->GetTimerManager().SetTimer(PlayerRespawnTimer, this, &AGameDev1AssGameModeBase::PlayerRespawnTimeUp, PlayerRespawnDuration, false);
	WarmUpCountdownCount = CreateWidget(GetWorld(), WarmUpCountdownClass);
	if (WarmUpCountdownCount) WarmUpCountdownCount->AddToViewport();
}

void AGameDev1AssGameModeBase::BeginEnemyRespawnProcess(AActor* Spawn)
{
	//Begins timer for Enemy Respawn.
	GetWorld()->GetTimerManager().SetTimer(EnemyRespawnTimer, this, &AGameDev1AssGameModeBase::EnemyRespawnTimeUp, EnemyRespawnDuration, false);
	TempEnemySpawns.Emplace(Spawn);
}

void AGameDev1AssGameModeBase::PlayerRespawnTimeUp()
{
	//Spawns Player in original location and Resets health and ammo.
	FVector SpawnLocation = PlayerSpawn->GetActorLocation();
	FRotator SpawnRotation = PlayerSpawn->GetActorRotation();
	APlayerCharacter* TempPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotation);
	PlayerControllerRef->RecastPlayerCharacter();
	PlayerControllerRef->ResetHealth();
	TempPlayer->SetOwner(this);
	bPlayerDead = false;
}

void AGameDev1AssGameModeBase::EnemyRespawnTimeUp()
{
	//Spawns Enemy(s) in original location(s).
	FVector SpawnLocation = TempEnemySpawns.Top()->GetActorLocation();
	FRotator SpawnRotation = TempEnemySpawns.Top()->GetActorRotation();
	AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation);
	TempEnemy->SetSpawnLocationActor(TempEnemySpawns.Top());
	TempEnemySpawns.RemoveSingle(TempEnemySpawns.Top());
	if (TempEnemySpawns.Num() != 0) EnemyRespawnTimeUp();
}

void AGameDev1AssGameModeBase::CleanUpTimeUp()
{
	//stops unnecessary ball and enemy spawnage.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), BallCleanup);
	for (AActor* ball : BallCleanup) {
		if (ball != inPlayBall) ball->Destroy();
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), EnemyCleanup);
	int counter = 0;
	for (AActor* Enemy : EnemyCleanup) {
		counter++;
		if (counter > 4) {
			if(bBallHeld == false) Enemy->Destroy();
		}
	}
	GetWorld()->GetTimerManager().SetTimer(CleanupTimer, this, &AGameDev1AssGameModeBase::CleanUpTimeUp, CleanupDuration, false);

}


void AGameDev1AssGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("StartGameCalled"));
	UGameplayStatics::PlaySound2D(GetWorld(), GameBackgroundMusic, BackgroundMusicVolume, 1.0f, 0.0f);
	PlayerControllerRef = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//Grabs locations of spawns to feed to RoundBeginSpawning.
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

	//Begins round beginning timer and stops play from happening.
	bPlayAllowed = false;
	GetWorld()->GetTimerManager().SetTimer(RoundBeginningTimer, this, &AGameDev1AssGameModeBase::GameBeginningTimeUp, RoundStartDuration, false);
	GetWorld()->GetTimerManager().SetTimer(CleanupTimer, this, &AGameDev1AssGameModeBase::CleanUpTimeUp, CleanupDuration, false);
	WarmUpCountdownCount = CreateWidget(GetWorld(), WarmUpCountdownClass);
	if (WarmUpCountdownCount) WarmUpCountdownCount->AddToViewport();
}

void AGameDev1AssGameModeBase::RoundBeginSpawning()
{
	//Spawns ball faced up in location specified and informs GameMode.
	if (BallSpawn) {
		FVector SpawnLocation = BallSpawn->GetActorLocation();
		FRotator SpawnRotation = FRotator(90.0f,0.0f,0.0f);
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
		TempBall->SetOwner(this);
		inPlayBall = TempBall;
	}

	//Spawns amount of Enemies equal to Target Points tags in locations specified.
	if (EnemySpawns.Num() != 0) {
		for (AActor* SpawnPoint : EnemySpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation);
			TempEnemy->SetSpawnLocationActor(SpawnPoint);
		}
	}
	//Spawns Player in location specified.
	if (PlayerSpawn) {
		FVector SpawnLocation = PlayerSpawn->GetActorLocation();
		FRotator SpawnRotation = PlayerSpawn->GetActorRotation();
		APlayerCharacter* TempPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, SpawnLocation, SpawnRotation);
		TempPlayer->SetOwner(this);
	}
}

void AGameDev1AssGameModeBase::RoundEndRemovals()
{
	//Removes Ball, All Players and Enemies for clean refresh.
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

	//Cancels or pauses all timers before clearing all actors, respawning them and beginning round start timer.
	GetWorld()->GetTimerManager().PauseTimer(EndMatchTimer);
	if (GetWorld()->GetTimerManager().IsTimerActive(PlayerRespawnTimer))GetWorld()->GetTimerManager().ClearTimer(PlayerRespawnTimer);
	if (GetWorld()->GetTimerManager().IsTimerActive(EnemyRespawnTimer))GetWorld()->GetTimerManager().ClearTimer(EnemyRespawnTimer);
	bPlayerDead = false;
	bPlayAllowed = false;
	RoundEndRemovals();
	UE_LOG(LogTemp, Warning, TEXT("RoundResetCalled"));
	RoundBeginSpawning();
	PlayerControllerRef->RecastPlayerCharacter();
	PlayerControllerRef->ResetHealth();

	if (WarmUpCountdownCount->GetIsEnabled()) WarmUpCountdownCount->RemoveFromViewport();

	GetWorld()->GetTimerManager().SetTimer(RoundBeginningTimer, this, &AGameDev1AssGameModeBase::RoundBeginningTimeUp, RoundStartDuration, false);
	WarmUpCountdownCount = CreateWidget(GetWorld(), WarmUpCountdownClass);
	if (WarmUpCountdownCount) WarmUpCountdownCount->AddToViewport();
}

void AGameDev1AssGameModeBase::TimeUp()
{
	//Checks if Player has more score than Enemy and transfers to appropiate victory screen.
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
	//Allows Player and Enemy to input actions.
	GetWorld()->GetTimerManager().UnPauseTimer(EndMatchTimer);
	bPlayAllowed = true;
	UE_LOG(LogTemp, Warning, TEXT("Play allowed value %s"), bPlayAllowed ? TEXT("true") : TEXT("false"));
}

void AGameDev1AssGameModeBase::GameBeginningTimeUp()
{
	//Allows Player and Enemy to input actions.
	MatchTimerCount = CreateWidget(GetWorld(), MatchTimerClass);
	bPlayAllowed = true;
	if (MatchTimerCount) MatchTimerCount->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(EndMatchTimer, this, &AGameDev1AssGameModeBase::TimeUp, MatchDuration, false);
}

FString AGameDev1AssGameModeBase::GetTime()
{
	//Used by UI to display acurate time to Player viewport.
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
	//Checks win condition and then opens relevant EndScreen.
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
