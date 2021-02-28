// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDev1AssGameModeBase.h"
#include "Ball.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateBallPosition.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTService_UpdateBallPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;
};
