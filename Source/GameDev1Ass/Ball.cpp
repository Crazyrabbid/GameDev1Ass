// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "EnemyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	BallMesh->SetupAttachment(RootComponent);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->SetSimulatePhysics(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 100.0f;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ABall::OnHit);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	//if (OtherActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass())) {
		AActor* ProjectileOwner = GetOwner();
		if (!ProjectileOwner) return;
		UGameplayStatics::ApplyDamage(OtherActor, baseDamage, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		//Destroy();
	//}
}