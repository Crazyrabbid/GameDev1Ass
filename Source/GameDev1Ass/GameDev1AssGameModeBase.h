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

	//Increases Players score. Spawns UI notice and either resets round or continues to end screen if over score threshold.
	UFUNCTION()
		void PlayerPointScored();

	//Increases Enemy score. Spawns UI notice and either resets round or continues to end screen if over score threshold.
	UFUNCTION()
		void EnemyPointScored();

	//Removes Ball and removes reference to avoid Crash.
	UFUNCTION()
		void DeleteBall();

	//Used to control if Enemy and Player can move or act.
	UFUNCTION()
		bool GetPlayAllowed();

	//Used to stop Player Controller trying to commit actions while Player is dead.
	UFUNCTION()
		bool GetPlayerDead();

	//Used to stop crash upon Enemy trying to read Ball location when not spawned.
	UFUNCTION()
		bool GetBallHeld();

	//Allows Enemy or Player to update if they have the Ball.
	UFUNCTION()
		void SetBallHeld(bool BallHeld);

	//Begins timer for Player respawn and initiates visual countdown.
	UFUNCTION()
		void BeginPlayerRespawnProcess();

	//Begins timer for Enemy Respawn.
	UFUNCTION()
		void BeginEnemyRespawnProcess(AActor* Spawn);

	UPROPERTY(EditAnywhere)
		ABall* inPlayBall;					  //Stores reference to currently used Ball for use in various functions.

protected:
	virtual void BeginPlay() override;

private:

	//Grabs locations of spawns to feed to RoundBeginSpawning and begins round beginning timer and stops play from happening.
	UFUNCTION()
		void StartGame();

	//Checks win condition and then opens relevant EndScreen.
	UFUNCTION()
		void GameOver(bool Win);

	//Cancels or pauses all timers before clearing all actors, respawning them and beginning round start timer.
	UFUNCTION()
		void RoundReset();

	//Checks if Player has more score than Enemy and transfers to appropiate victory screen.
	UFUNCTION()
		void TimeUp();

	//Spawns Ball, Player and Enemies in specified positions.
	UFUNCTION()
		void RoundBeginSpawning();

	//Removes Ball, All Players and Enemies for clean refresh.
	UFUNCTION()
		void RoundEndRemovals();

	//Allows Player and Enemy to input actions.
	UFUNCTION()
		void RoundBeginningTimeUp();

	//Allows Player and Enemy to input actions.
	UFUNCTION()
		void GameBeginningTimeUp();

	//Spawns Player in original location and Resets health and ammo.
	UFUNCTION()
		void PlayerRespawnTimeUp();

	//Spawns Enemy(s) in original location(s).
	UFUNCTION()
		void EnemyRespawnTimeUp();

	//Cleans up unwanted actors.
	UFUNCTION()
		void CleanUpTimeUp();

	//Used by UI to display acurate time to Player viewport.
	UFUNCTION(BlueprintPure)
		FString GetTime();

	//Used by UI to display acurate Player score to Player viewport.
	UFUNCTION(BlueprintPure)
		float GetBlueScore();

	//Used by UI to display acurate Enemy score to Player viewport.
	UFUNCTION(BlueprintPure)
		float GetRedScore();


	UPROPERTY(EditAnywhere) int scoreLimit = 3;		//Adjustable threshold for Player or Enemies team to overcome scorewise.
	UPROPERTY() int playerTeamScore = 0;			//Tracker for Player's Score to track victory conditions with.
	UPROPERTY() int enemyTeamScore = 0;				//Tracker for Enemie's score to track victory conditions with.

	UPROPERTY() TArray<AActor*> Targets;				  //Stores positions and rotations of all Target Points within Level for flitering.
	UPROPERTY() AActor* BallSpawn;						  //Position and Rotation for spawning Ball.
	UPROPERTY() AActor* PlayerSpawn;					  //Position and Rotation for spawning Player.
	UPROPERTY() TArray<AActor*> TempEnemySpawns;		  //Stores positions and rotations of all Enemy spawns within Level for flitering.
	UPROPERTY() TArray<AActor*> EnemySpawns;			  //Position and Rotation for spawning Enemies.

	UPROPERTY() TArray<AActor*> BallCleanup;				  //Stores positions and rotations of all balls within Level for flitering.
	UPROPERTY() TArray<AActor*> EnemyCleanup;				  //Stores positions and rotations of all enemy within Level for flitering.

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> BlueTeamScoredClass;		  //Blueprint to create and attach Blue Scored Notice to viewport.
	UPROPERTY() UUserWidget* BlueTeamScoredCount;								  //Monitors UI from Inception and is used as an interface to the UI.
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> RedTeamScoredClass;		  //Blueprint to create and attach Red Scored Notice to viewport.
	UPROPERTY() UUserWidget* RedTeamScoredCount;								  //Monitors UI from Inception and is used as an interface to the UI.
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> WarmUpCountdownClass;		  //Blueprint to create and attach Death/Round Beginning Timer to viewport.
	UPROPERTY() UUserWidget* WarmUpCountdownCount;								  //Monitors UI from Inception and is used as an interface to the UI.
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> MatchTimerClass;			  //Blueprint to create and attach Match Timer to viewport.
	UPROPERTY() UUserWidget* MatchTimerCount;									  //Monitors UI from Inception and is used as an interface to the UI.


	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;						//Blueprint used as a template to create Ball.
	UPROPERTY(EditAnywhere) TSubclassOf <AEnemyCharacter> EnemyClass;			//Blueprint used as a template to create Enemy.
	UPROPERTY(EditAnywhere) TSubclassOf <APlayerCharacter> PlayerClass;			//Blueprint used as a template to create Player.
	UPROPERTY(EditAnywhere) USoundBase* GameBackgroundMusic;					//Sound file to play Background Music.
	UPROPERTY(EditAnywhere) float BackgroundMusicVolume = 1.0f;					//Volume to play Background Music.
	UPROPERTY() AEnemyAIController* EnemyAIControllerRef;						
	UPROPERTY() ACustomPlayerController* PlayerControllerRef;					


	UPROPERTY() FTimerHandle EndMatchTimer;									//Handle for match duration timer.
	UPROPERTY(EditAnywhere) float MatchDuration = 300.0f;					//Adjustable time it takes for match to occur.
	UPROPERTY() FTimerHandle RoundBeginningTimer;							//Handle for warmup timer.
	UPROPERTY(EditAnywhere) float RoundStartDuration = 4.0f;				//Adjustable time it takes to begin a round.
	UPROPERTY() FTimerHandle PlayerRespawnTimer;							//Handle for player respawn timer.
	UPROPERTY(EditAnywhere) float PlayerRespawnDuration = 3.0f;				//Adjustable time it takes to respawn player.
	UPROPERTY() FTimerHandle EnemyRespawnTimer;								//Handle for enemy respawn timer.
	UPROPERTY(EditAnywhere) float EnemyRespawnDuration = 3.0f;				//Adjustable time it takes to respawn enemy.
	UPROPERTY() FTimerHandle CleanupTimer;									//Handle for cleanup timer.
	UPROPERTY(EditAnywhere) float CleanupDuration = 0.5f;					//Adjustable time it takes between Cleanups.

	UPROPERTY() bool bPlayAllowed = false;			  //Overriding Bool to stop Player and Enemy interacting during Warmup.
	UPROPERTY() bool bPlayerDead = false;			  //Overriding Bool to stop Player interacting when dead.
	UPROPERTY() bool bBallHeld = false;				  //Overriding Bool to stop functions relying on Ball from occuring when Ball is non-physical.

};
