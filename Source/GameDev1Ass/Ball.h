// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class GAMEDEV1ASS_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION() void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 2500.0f;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BallMesh;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere)
		float baseDamage = 100.0f;
};
