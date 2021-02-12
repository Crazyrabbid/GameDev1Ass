// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTrigger.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AGoalTrigger::AGoalTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Goal Mesh"));
	SetRootComponent(GoalMesh);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AGoalTrigger::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGoalTrigger::OnOverlapEnd);
	GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AGoalTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (GameModeRef) {
		if (OtherActor == GameModeRef->inPlayBall) {
			if (playerGoal) GameModeRef->EnemyPointScored();
			else GameModeRef->PlayerPointScored();
		}
	}
}

void AGoalTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}

// Called every frame
void AGoalTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

