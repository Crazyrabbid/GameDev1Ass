// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CustomPlayerController.h"
#include "GravLift.h"

// Sets default values
AGravLift::AGravLift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GravLiftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grav Lift Mesh"));
	SetRootComponent(GravLiftMesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

	ForceOriginPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Force Origin Point"));
	ForceOriginPoint->SetupAttachment(RootComponent);
	ForceOriginPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

// Called when the game starts or when spawned
void AGravLift::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGravLift::OnOverlapBegin);
	playerController = Cast<ACustomPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

// Called every frame
void AGravLift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGravLift::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->FindComponentByClass(UCharacterMovementComponent::StaticClass())) {
		if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
			if(playerController) playerController->GravLift(ForceOriginPoint->GetForwardVector() * forceStrength, false, true);
		}
	}
	else {
		UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());

		UE_LOG(LogTemp, Warning, TEXT("GravLiftOnOverlapCalled, %s"), *RootComp->GetName());
		RootComp->AddImpulse(ForceOriginPoint->GetForwardVector() * forceStrength * RootComp->GetMass());
	}
}


