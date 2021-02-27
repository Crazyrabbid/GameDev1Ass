// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "PlayerCharacter.h"
#include "GameDev1AssGameModeBase.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

void ACustomPlayerController::BeginPlay() {
	Super::BeginPlay();
	playerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	}
	else if (GetWorld()->GetName() == (TEXT("EndScreen"))) {
		GameModeRef = nullptr;
	}
	playerHealth = playerHealthMax;
	gunClipAmmo = gunClipSize;
	PlayerHUDCount = CreateWidget(this, PlayerHUDClass);
	if (PlayerHUDCount) PlayerHUDCount->AddToViewport();
	MiniMapCount = CreateWidget(GetWorld(), MiniMapClass);
	if (MiniMapCount) MiniMapCount->AddToViewport();

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
	InputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ACustomPlayerController::Reload);
	InputComponent->BindAction(TEXT("Catch"), IE_Pressed, this, &ACustomPlayerController::Catch);
}

void ACustomPlayerController::JumpCharacter()
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->Jump();
}

void ACustomPlayerController::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Fire Pressed"));
	if (GetPlayAllowed()) {
		if (bBallHeld) {
			UE_LOG(LogTemp, Warning, TEXT("Ball Held"));
			if (playerCharacter) playerCharacter->Fire();
			bBallHeld = false;
		}
		else {
			if (gunClipAmmo > 0) {
				gunClipAmmo--;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSoundEffect, playerCharacter->GetActorLocation(), ShotSoundVolume, 1.0f, 0.0f);
				FVector cameraLocation;
				FRotator cameraRotation;
				GetPlayerViewPoint(cameraLocation, cameraRotation);

				FVector end = cameraLocation + cameraRotation.Vector() * castRange;

				FHitResult Hit;
				FCollisionQueryParams lineTraceParams;

				lineTraceParams.AddIgnoredActor(playerCharacter);
				bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, cameraLocation, end, ECC_Pawn, lineTraceParams);
				if (bDidHit && Hit.GetActor() != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());
					if (Hit.GetActor()->FindComponentByClass(UCharacterMovementComponent::StaticClass())) {

					}
					else {
						UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
						RootComp->AddImpulse(cameraRotation.Vector() * impulseForce * RootComp->GetMass());
					}
					UGameplayStatics::ApplyDamage(Hit.GetActor(), gunBaseDamage, this, playerCharacter, UDamageType::StaticClass());
					ADamagePointVisualiser* TempDamageVisualiser = GetWorld()->SpawnActor<ADamagePointVisualiser>(DamagePointClass, Hit.ImpactPoint, cameraRotation);
				}
			}
			else {
				OutOfAmmoCount = CreateWidget(this, OutOfAmmoClass);
				if (OutOfAmmoCount) OutOfAmmoCount->AddToViewport();
			}
		}
	}
}

void ACustomPlayerController::Reload() {
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSoundEffect, playerCharacter->GetActorLocation(), ReloadSoundVolume, 1.0f, 0.0f);
	gunClipAmmo = gunClipSize;
}

void ACustomPlayerController::Catch() {
	UE_LOG(LogTemp, Warning, TEXT("Catch Pressed"));
	if (GameModeRef != nullptr) {
		if (playerCharacter && GetPlayAllowed()) {
			FVector cameraLocation;
			FRotator cameraRotation;
			GetPlayerViewPoint(cameraLocation, cameraRotation);

			FVector end = cameraLocation + cameraRotation.Vector() * castRange;

			FHitResult Hit;
			FCollisionQueryParams lineTraceParams;

			lineTraceParams.AddIgnoredActor(playerCharacter);
			bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, cameraLocation, end, ECC_Pawn, lineTraceParams);

			if (bDidHit && Hit.GetActor() == GameModeRef->inPlayBall && Hit.Distance < ballPickUpDistance) {
				bBallHeld = true;
				UE_LOG(LogTemp, Warning, TEXT("Ball Held value %s"), bBallHeld ? TEXT("true") : TEXT("false"));
				GameModeRef->DeleteBall();
			}
		}
	}
}


void ACustomPlayerController::MoveForwards(float axisAmount)
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->AddMovementInput(playerCharacter->GetActorForwardVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Strafe(float axisAmount)
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->AddMovementInput(playerCharacter->GetActorRightVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Turn(float axisAmount)
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->AddControllerPitchInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Pitch(float axisAmount)
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->AddControllerYawInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::GravLift(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	if (playerCharacter && GetPlayAllowed()) playerCharacter->LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
}

float ACustomPlayerController::GetHealth()
{
	return playerHealth;
}

float ACustomPlayerController::GetHealthTotal()
{
	return playerHealthMax;
}

float ACustomPlayerController::GetAmmo()
{
	return gunClipAmmo;
}

float ACustomPlayerController::GetAmmoTotal()
{
	return gunClipSize;
}

bool ACustomPlayerController::GetPlayAllowed()
{
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		return GameModeRef->GetPlayAllowed();
	}
	else {
		return true;
	}
}

float ACustomPlayerController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	playerHealth -= DamageAmount;
	if (playerHealth <= 0) playerCharacter->Destroy();
	return DamageAmount;
}

void ACustomPlayerController::RecastPlayerCharacter()
{
	playerCharacter = Cast<APlayerCharacter>(GetPawn());
}
