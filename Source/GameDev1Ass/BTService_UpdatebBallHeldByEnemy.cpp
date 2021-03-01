// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatebBallHeldByEnemy.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdatebBallHeldByEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	//Ensures function only works in level with Ball present.
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
		bool bBallHeld = EnemyCharacter->BallHeld();		

		//Checks if Enemy has Ball to allow them to head to player goal and try and score.
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