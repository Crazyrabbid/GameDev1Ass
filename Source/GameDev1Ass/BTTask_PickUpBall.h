// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RunBehavior.h"
#include "BTTask_PickUpBall.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTTask_PickUpBall : public UBTTask_RunBehavior
{
	GENERATED_BODY()
	
protected:
	//Grabs if Enemy has Ball so they can head to Player goal and score.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
