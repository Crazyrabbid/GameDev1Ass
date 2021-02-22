// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagePointVisualiser.generated.h"

UCLASS()
class GAMEDEV1ASS_API ADamagePointVisualiser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagePointVisualiser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DamageVisualiserMesh;
};
