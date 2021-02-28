// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ThrowAtGoal.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_ThrowAtGoal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ABall* BallPawn = GameModeRef->inPlayBall;
	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	if (BallClass) {
		UE_LOG(LogTemp, Warning, TEXT("Fire Activated, Ball Class Exists"));
		FVector SpawnLocation = AIActor->GetActorLocation();
		FRotator SpawnRotation = AIActor->GetActorRotation();
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("inPlayBall Assigned"));
			GameModeRef->inPlayBall = TempBall;
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
