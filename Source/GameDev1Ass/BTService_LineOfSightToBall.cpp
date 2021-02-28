// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LineOfSightToBall.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LineOfSightToBall::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (GetWorld()->GetName() == (TEXT("ArenaLevel")) || GetWorld()->GetName() == (TEXT("DevMap"))) {
		AAIController* EnemyAIController = OwnerComp.GetAIOwner();
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		ABall* BallPawn = GameModeRef->inPlayBall;

		if (EnemyAIController->LineOfSightTo(BallPawn)) {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		}
		else {
			EnemyAIController->ClearFocus(EAIFocusPriority::Default);
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
}
