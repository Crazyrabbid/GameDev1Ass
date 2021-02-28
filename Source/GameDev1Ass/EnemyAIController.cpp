// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "GameDev1AssGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

void AEnemyAIController::OnPossess(APawn* InPawn){
	Super::OnPossess(InPawn);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ABall* BallPawn = NULL;
	if(GameModeRef) BallPawn = GameModeRef->inPlayBall;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	for (AActor* Waypoint : Waypoints) {
		if (Waypoint->ActorHasTag(TEXT("LookOut"))) LookOutPoint = Waypoint; 
		else if (Waypoint->ActorHasTag(TEXT("Home"))) HomePoint = Waypoint;
		else if (Waypoint->ActorHasTag(TEXT("AIScorePosition"))) ScorePoint = Waypoint;
	}
	
	if(BT_EnemyAI != NULL) RunBehaviorTree(BT_EnemyAI);
	if (HomePoint != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), HomePoint->GetActorLocation());
	if (LookOutPoint != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("LookOutPosition"), LookOutPoint->GetActorLocation());
	if (PlayerPawn != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
	if (BallPawn != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("BallPosition"), BallPawn->GetActorLocation());
	if (ScorePoint != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("AIScorePosition"), ScorePoint->GetActorLocation());
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

