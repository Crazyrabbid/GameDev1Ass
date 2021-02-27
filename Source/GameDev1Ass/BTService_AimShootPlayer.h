// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AimShootPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API UBTService_AimShootPlayer : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float gunBaseDamage = 20.0f;
	UPROPERTY(EditAnywhere)
		float castRange = 10000.0f;
	UPROPERTY(EditAnywhere)
		float impulseForce = 500.0f;
	UPROPERTY(EditAnywhere) USoundBase* ShotSoundEffect;
	UPROPERTY(EditAnywhere) float ShotSoundVolume = 1.0f;
};
