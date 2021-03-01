// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDev1AssGameModeBase.h"
#include "Ball.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateDistanceToBall.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTService_UpdateDistanceToBall : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	//Calculates Enemy's distance to Ball through the square root of a dot product.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;			//Used to grab reference to Ball.
};
