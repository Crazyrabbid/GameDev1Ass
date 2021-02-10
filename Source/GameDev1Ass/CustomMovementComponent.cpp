//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "CustomMovementComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//
//// Sets default values for this component's properties
//UCustomMovementComponent::UCustomMovementComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UCustomMovementComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//
//// Called every frame
//void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
//
//void UCustomMovementComponent::MoveForwards(float axisAmount)
//{
//	FVector DeltaLocation = FVector(axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
//	GetOwner()->AddActorLocalOffset(DeltaLocation, true);
//}
//
//void UCustomMovementComponent::JumpCharacter()
//{
//	//GetOwner->Jump();
//}
//
//void UCustomMovementComponent::Strafe(float axisAmount)
//{
//	FVector DeltaLocation = FVector(0.0f, axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f);
//	GetOwner()->AddActorLocalOffset(DeltaLocation, true);
//}
//
//void UCustomMovementComponent::Turn(float axisAmount)
//{
//	float rotateAmount = axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds;
//	FRotator rotation = FRotator(0.0f, rotateAmount, 0.0f);
//	GetOwner()->AddActorLocalRotation(FQuat(rotation), true);
//}
//
//void UCustomMovementComponent::Pitch(float axisAmount)
//{
//	float rotateAmount = axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds;
//	FRotator rotation = FRotator(0.0f, 0.0f, rotateAmount);
//	GetOwner()->AddActorLocalRotation(FQuat(rotation), true);
//}