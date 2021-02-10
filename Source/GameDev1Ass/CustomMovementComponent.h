//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "CustomMovementComponent.generated.h"
//
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class GAMEDEV1ASS_API UCustomMovementComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	// Sets default values for this component's properties
//	UCustomMovementComponent();
//	void MoveForwards(float axisAmount);
//	void JumpCharacter();
//	void Fire();
//	void Strafe(float axisAmount);
//	void Turn(float axisAmount);
//	void Pitch(float axisAmount);
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//private: 
//	UPROPERTY(EditAnywhere)
//		float moveSpeed = 100.0f;
//	UPROPERTY(EditAnywhere)
//		float rotationSpeed = 500.0f;
//		
//};
