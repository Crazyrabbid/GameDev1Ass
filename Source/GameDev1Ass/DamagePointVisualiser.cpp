// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePointVisualiser.h"

// Sets default values
ADamagePointVisualiser::ADamagePointVisualiser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DamageVisualiserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunDamageMesh"));
	SetRootComponent(DamageVisualiserMesh);
	DamageVisualiserMesh->SetNotifyRigidBodyCollision(false);
	DamageVisualiserMesh->SetSimulatePhysics(false);
	InitialLifeSpan = 2.0f;
	
}

// Called when the game starts or when spawned
void ADamagePointVisualiser::BeginPlay()
{
	Super::BeginPlay();
}


