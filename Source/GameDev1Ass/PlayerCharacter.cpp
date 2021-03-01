// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameDev1AssGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Generates and sets up springArm to ensure consistent third person camera control.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->CameraLagSpeed = 20.0f;
	SpringArm->CameraRotationLagSpeed = 20.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	//Creates camera and attaches to Spring arm.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-400.0f, 0.0f, 350.0f));
	Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	//Creates location to fire Ball from.
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
	ProjectileSpawnPoint->SetRelativeLocation(FVector(10.0f, 20.0f, 100.0f));

	//Spring arm created and set up to create a consistent mini map camera with.
	MapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Map Arm"));
	MapArm->SetupAttachment(GetMesh());
	MapArm->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	MapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, -90.0f));

	//Creates and attaches mini map camera to spring arm.
	MapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Map Camera"));
	MapCapture->SetupAttachment(MapArm);

	GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APlayerCharacter::Fire() {

	//Spawns a Ball and informs GameMode of Ball creation.
	UE_LOG(LogTemp, Warning, TEXT("Fire Activated"));
	if (BallClass) {
		UE_LOG(LogTemp, Warning, TEXT("Fire Activated, Ball Class Exists"));
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = Camera->GetComponentRotation();
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
		TempBall->SetOwner(this);
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("inPlayBall Assigned"));
			GameModeRef->inPlayBall = TempBall;
		}
	}
}

void APlayerCharacter::BallDropped()
{
	//Spawns a ball pointed down up death.
	if (BallClass) {
		UE_LOG(LogTemp, Warning, TEXT("Fire Activated, Ball Class Exists"));
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, -90.0f);
		ABall* TempBall = GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocation, SpawnRotation);
		TempBall->SetOwner(this);
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("inPlayBall Assigned"));
			GameModeRef->inPlayBall = TempBall;
		}
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//Sends damage notification through to controller to handle.
	GetController()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}
