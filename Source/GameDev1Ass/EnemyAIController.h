// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ball.h"
#include "EnemyAIController.generated.h"

class AGameDev1AssGameModeBase;

UCLASS()
class GAMEDEV1ASS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		TArray<AActor*> Waypoints;						//Stores all TargetPoints from Map to sort through.
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BT_EnemyAI;					    //Behaviour tree for Enemy to run.
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;			//Used to grab reference to Ball.
public:
	UPROPERTY()
		AActor* LookOutPoint;							//Location for Enemy to navigate to.
	UPROPERTY()
		AActor* HomePoint;								//Location for Enemy to navigate to.
	UPROPERTY()
		AActor* ScorePoint;								//Location for Enemy to throw ball from.

};
