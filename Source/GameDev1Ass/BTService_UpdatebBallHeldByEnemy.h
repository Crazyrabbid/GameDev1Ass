// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatebBallHeldByEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTService_UpdatebBallHeldByEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	//Checks if Enemy has Ball to allow them to head to player goal and try and score.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
