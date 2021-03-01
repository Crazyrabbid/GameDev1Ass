// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GameDev1AssGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = AEnemyAIController::StaticClass();
	SpawnDefaultController();
	DisableComponentsSimulatePhysics();

	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	}
	else if (GetWorld()->GetName() == (TEXT("EndScreen"))) {
		GameModeRef = nullptr;
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetSpawnLocationActor(AActor* SpawnLocationActor)
{
	//Records spawn location to give to GameMode upon death for respawning.
	SpawnLocation = SpawnLocationActor;
}

void AEnemyCharacter::PickUpBall()
{
	//Deletes Ball and possesses it.
	bBallHeld = true;
	GameModeRef->DeleteBall();
	GameModeRef->SetBallHeld(true);
}

bool AEnemyCharacter::BallHeld()
{
	//Returns Ball Held to allow Enemy to head to Player goal and score.
	return bBallHeld;
}

void AEnemyCharacter::BallDropped()
{
	//Spawns ball pointed down upon death and notifys.
	if (BallClass) {
		UE_LOG(LogTemp, Warning, TEXT("Fire Activated, Ball Class Exists"));
		FVector BallSpawnLocation = GetActorLocation();
		FRotator BallSpawnRotation = FRotator(0.0f, 0.0f, -90.0f);
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, BallSpawnLocation, BallSpawnRotation);
		TempBall->SetOwner(this);
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("inPlayBall Assigned"));
			GameModeRef->inPlayBall = TempBall;
			GameModeRef->SetBallHeld(false);
		}
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= DamageAmount;

	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	if (Health <= 0) {
		GameModeRef->BeginEnemyRespawnProcess(SpawnLocation);
		if (bBallHeld) {
			BallDropped();
			bBallHeld = false;
		}
		Destroy(); 
	}
	return DamageAmount;
}