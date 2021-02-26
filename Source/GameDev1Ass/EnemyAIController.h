// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class GAMEDEV1ASS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		TArray<AActor*> Waypoints;
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BT_EnemyAI;
public:
	UPROPERTY()
		AActor* LookOutPoint;
	UPROPERTY()
		AActor* HomePoint;
};
