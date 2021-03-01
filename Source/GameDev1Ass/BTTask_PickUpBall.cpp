// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PickUpBall.h"
#include "EnemyCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_PickUpBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only runs on level with Ball.
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {

		//Grabs if Enemy has Ball so they can head to Player goal and score.
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
		if (EnemyCharacter) EnemyCharacter->PickUpBall();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
 }
