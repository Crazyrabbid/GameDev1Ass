// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatebBallHeldByEnemy.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdatebBallHeldByEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
		bool bBallHeld = EnemyCharacter->BallHeld();
		if (EnemyCharacter) {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bBallHeld);
		}
		else {
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}