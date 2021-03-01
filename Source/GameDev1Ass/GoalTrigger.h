// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameDev1AssGameModeBase.h"
#include "GoalTrigger.generated.h"

UCLASS()
class GAMEDEV1ASS_API AGoalTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Triggers Point scored dependant on Bool checked.
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Kinda useless but got attachment issues to it.
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GoalMesh;					  //Visual representation of Goal.
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;					  //Used to check if Ball has entered the tunnel to trigger goal.
	UPROPERTY(EditAnywhere)
		bool playerGoal;								  //If ticked, Enemy scored. Else Player Scored.
	UPROPERTY()
		AGameDev1AssGameModeBase* GameModeRef;			  //Used to inform Gamemode that player or enemy has scored.
};
