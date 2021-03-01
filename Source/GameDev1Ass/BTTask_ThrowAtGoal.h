// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDev1AssGameModeBase.h"
#include "Ball.h"
#include "BehaviorTree/Tasks/BTTask_RunBehavior.h"
#include "BTTask_ThrowAtGoal.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTTask_ThrowAtGoal : public UBTTask_RunBehavior
{
	GENERATED_BODY()
	
protected:
	//Spawns Ball which gets thrown into Goal for Enemy to score.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;					  //Reference to GameMode to notify that Ball has been scored.
	UPROPERTY(EditAnywhere) TSubclassOf<ABall> BallClass;		  //Reference to Ball class to spawn it.

};
