// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "EnemyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates mesh for Ball and enables collision
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	SetRootComponent(BallMesh);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->SetSimulatePhysics(true);

	//Initiates Ball as a projectile to give it momentum upon creation. Also stops it despawning.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 0;
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

	//Stops Ball falling out of map and if so notifys player
	if (GetActorLocation().Z > 2000.0f || GetActorLocation().Z < 0.0f) {
		SetActorLocation(FVector(300.0f, 600.0f, 20.0f));
		BallResetNoticeCount = CreateWidget(GetWorld(), BallResetNoticeClass);
		if (BallResetNoticeCount) BallResetNoticeCount->AddToViewport();
	}

}

void ABall::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
		AActor* ProjectileOwner = GetOwner();
		if (!ProjectileOwner) return;

		//Upon hit plays sound and applies damage if above certain force.
		if (NormalImpulse.Size() > ForceSoundCutoffAmount) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), BounceSoundEffect, Hit.Location, BounceSoundVolume * NormalImpulse.Size(), 1.0f, 0.0f);
			UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		}
}