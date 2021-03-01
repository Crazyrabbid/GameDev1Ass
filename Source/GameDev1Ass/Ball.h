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
	//Upon hit plays sound and applies damage if above certain force.
	UFUNCTION() void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 2500.0f;										 //Used to set speed Ball spawns with and can achieve.
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BallMesh;										 //Mesh used to display Ball to player.
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;					 //Used to apply movement to Ball upon spawn.
	UPROPERTY(EditAnywhere)
		float BaseDamage = 100.0f;											 //Damage Ball does when OnHit is triggered.
	UPROPERTY(EditAnywhere)
		float ForceSoundCutoffAmount = 0.5f;								 //Barrier force has to overcome to trigger OnHit.
	UPROPERTY(EditAnywhere) USoundBase* BounceSoundEffect;					 //Sound Ball plays OnHit.
	UPROPERTY(EditAnywhere) float BounceSoundVolume = 1.0f;					 //Volume of OnHit Sound.
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> BallResetNoticeClass;	 //UI notification of Ball being Reset.
	UPROPERTY() UUserWidget* BallResetNoticeCount;							 //Handle for the creation and monitoring of Ball being Reset UI notification.
};
