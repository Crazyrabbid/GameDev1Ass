// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPosition.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

 EBTNodeResult::Type UBTTask_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	 Super::ExecuteTask(OwnerComp, NodeMemory);

	 if (OwnerComp.GetAIOwner() == nullptr) {
		 return EBTNodeResult::Failed;
	 }

	 AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	 float RandomRadius = 2000.0f;
	 FNavLocation RandomLocation;

	 UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	 NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);

	 OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), RandomLocation);

	 return EBTNodeResult::Succeeded;
}
