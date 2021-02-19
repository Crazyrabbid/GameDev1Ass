// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACustomPlayerController::BeginPlay() {
	Super::BeginPlay();
	playerCharacter = Cast<APlayerCharacter>(GetPawn());
	GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	PlayerHUDCount = CreateWidget(this, PlayerHUDClass);
	if (PlayerHUDCount) PlayerHUDCount->AddToViewport();
	playerHealth = playerHealthMax;
}

void ACustomPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis(TEXT("Forward"), this, &ACustomPlayerController::MoveForwards);
	InputComponent->BindAxis(TEXT("Strafe"), this, &ACustomPlayerController::Strafe);
	InputComponent->BindAxis(TEXT("Turn"), this, &ACustomPlayerController::Turn);
	InputComponent->BindAxis(TEXT("Pitch"), this, &ACustomPlayerController::Pitch);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACustomPlayerController::JumpCharacter);
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACustomPlayerController::Fire);
	InputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ACustomPlayerController::Fire);
	InputComponent->BindAction(TEXT("Catch"), IE_Pressed, this, &ACustomPlayerController::Catch);
}

void ACustomPlayerController::JumpCharacter()
{
	if (playerCharacter) playerCharacter->Jump();
}

void ACustomPlayerController::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Fire Pressed"));
	playerHealth--;
	if (BallHeld) {
		UE_LOG(LogTemp, Warning, TEXT("Ball Held"));
		if (playerCharacter) playerCharacter->Fire();
		BallHeld = false;
	}
}

void ACustomPlayerController::Catch() {
	UE_LOG(LogTemp, Warning, TEXT("Catch Pressed"));
	if (playerCharacter) {
		UE_LOG(LogTemp, Warning, TEXT("Catch Pressed, Player Character exists"));
		//if (playerCharacter->ActorLineTraceSingle());
		BallHeld = true;
		GameModeRef->DeleteBall();
	}
}


void ACustomPlayerController::MoveForwards(float axisAmount)
{
	if (playerCharacter) playerCharacter->AddMovementInput(playerCharacter->GetActorForwardVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Strafe(float axisAmount)
{
	if (playerCharacter) playerCharacter->AddMovementInput(playerCharacter->GetActorRightVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Turn(float axisAmount)
{
	if (playerCharacter) playerCharacter->AddControllerPitchInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Pitch(float axisAmount)
{
	if (playerCharacter) playerCharacter->AddControllerYawInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

float ACustomPlayerController::GetHealth()
{
	return playerHealth;
}

float ACustomPlayerController::GetHealthTotal()
{
	return playerHealthMax;
}
