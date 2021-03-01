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

	//Obtains Player character and a reference to AGameDev1AssGameModeBase.
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	}
	else if (GetWorld()->GetName() == (TEXT("EndScreen"))) {
		GameModeRef = nullptr;
	}

	//Sets health and ammo to Blueprinted amount and displays counters.
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
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->Jump();
}

void ACustomPlayerController::Fire() {

	//Ensures function is only used when Player is alive and able.
	UE_LOG(LogTemp, Warning, TEXT("Fire Pressed"));
	if (GetPlayAllowed() && !GetPlayerDied() && !bReloading) {

		//Throws Ball if Held.
		if (bBallHeld) {
			UE_LOG(LogTemp, Warning, TEXT("Ball Held"));
			if (PlayerCharacter) PlayerCharacter->Fire();
			GameModeRef->SetBallHeld(false);
			bBallHeld = false;
		}

		//Else shoots from gun.
		else {
			if (gunClipAmmo > 0) {			
				gunClipAmmo--;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSoundEffect, PlayerCharacter->GetActorLocation(), ShotSoundVolume, 1.0f, 0.0f);

				//Uses camera location and rotation to know where to begin line trace.
				FVector cameraLocation;
				FRotator cameraRotation;
				GetPlayerViewPoint(cameraLocation, cameraRotation);

				//Endpoint of line trace that checks if bullet hits something.
				FVector end = cameraLocation + cameraRotation.Vector() * castRange;

				FHitResult Hit;								    //Stores hit information after line trace.
				FCollisionQueryParams lineTraceParams;		    //Configuration for the line trace to stop Enemy shooting themselves.

				lineTraceParams.AddIgnoredActor(PlayerCharacter);
				bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, cameraLocation, end, ECC_Pawn, lineTraceParams);		//Checks hit was made to avoid possible memory leaks.
				if (bDidHit && Hit.GetActor() != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());
					if (Hit.GetActor()->FindComponentByClass(UCharacterMovementComponent::StaticClass())) {		  //Stops physics force being applied to objects that can't handle physics.

					}
					else {
						UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());	 //Retrieves actor that was shot to add force.
						RootComp->AddImpulse(cameraRotation.Vector() * impulseForce * RootComp->GetMass());
					}
					UGameplayStatics::ApplyDamage(Hit.GetActor(), gunBaseDamage, this, PlayerCharacter, UDamageType::StaticClass());	 //Applies damage to shot actor. Requires them to have takeDamage function.
					ADamagePointVisualiser* TempDamageVisualiser = GetWorld()->SpawnActor<ADamagePointVisualiser>(DamagePointClass, Hit.ImpactPoint, cameraRotation);	 //Spawns object at position of hit to notify player where shot hit.
				}
			}
			else {	   //Displays UI notice to player that they're out of ammo.
				OutOfAmmoCount = CreateWidget(this, OutOfAmmoClass);
				if (OutOfAmmoCount) OutOfAmmoCount->AddToViewport();
			}
		}
	}
}

void ACustomPlayerController::Reload() {
	//Begins reload process and stops player from shooting.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSoundEffect, PlayerCharacter->GetActorLocation(), ReloadSoundVolume, 1.0f, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACustomPlayerController::ReloadTimeUp, ReloadBulletDuration, false);
	bReloading = true;
}

void ACustomPlayerController::Catch() {
	UE_LOG(LogTemp, Warning, TEXT("Catch Pressed"));

	//Runs line trace to check if player under PickUpDistance where the Ball would be deleted and given possession to player.
	if (GameModeRef != nullptr) {
		if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied() && !bReloading) {
			//Grabs viewpoint to begin line trace from.
			FVector cameraLocation;
			FRotator cameraRotation;
			GetPlayerViewPoint(cameraLocation, cameraRotation);

			//Calculates end point of line trace.
			FVector end = cameraLocation + cameraRotation.Vector() * castRange;

			FHitResult Hit;									   //Stores hit information after line trace.
			FCollisionQueryParams lineTraceParams;			   //Configuration for the line trace to stop player collider interferring with picking Ball up

			lineTraceParams.AddIgnoredActor(PlayerCharacter);
			bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, cameraLocation, end, ECC_Pawn, lineTraceParams);	//Checks hit was made to avoid possible memory leaks.

			if (bDidHit && Hit.GetActor() == GameModeRef->inPlayBall && Hit.Distance < ballPickUpDistance) {		 //Deletes Ball and stores it within player notifying Gamemode.
				bBallHeld = true;
				UE_LOG(LogTemp, Warning, TEXT("Ball Held value %s"), bBallHeld ? TEXT("true") : TEXT("false"));
				GameModeRef->DeleteBall();
				GameModeRef->SetBallHeld(true);
			}
		}
	}
}


void ACustomPlayerController::MoveForwards(float axisAmount)
{
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Strafe(float axisAmount)
{
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector() * axisAmount * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Turn(float axisAmount)
{
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->AddControllerPitchInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::Pitch(float axisAmount)
{
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->AddControllerYawInput(axisAmount * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACustomPlayerController::GravLift(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) //Allows player to use grav lift by using CharacterMovementComponent's alternative to forces.
{
	if (PlayerCharacter && GetPlayAllowed() && !GetPlayerDied()) PlayerCharacter->LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
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
	if (bBallHeld) {
		return 1;
	}
	else {
		return gunClipAmmo;
	}
}

float ACustomPlayerController::GetAmmoTotal()
{
	if (bBallHeld) {
		return 1;
	}
	else {
		return gunClipSize;
	}
}

FString ACustomPlayerController::GetItemEquiped()
{
	if (bBallHeld) {
		return TEXT("Ball");
	}
	else {
		return TEXT("Gun");
	}
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

bool ACustomPlayerController::GetPlayerDied()
{
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))) {
		return GameModeRef->GetPlayerDead();
	}
	else {
		return false;
	}
}

void ACustomPlayerController::ReloadTimeUp()
{
	//Applies ammo recursively until max ammo.
	if (gunClipAmmo != gunClipSize) {
		gunClipAmmo++;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACustomPlayerController::ReloadTimeUp, ReloadBulletDuration, false);
	}
	bReloading = false;
}

float ACustomPlayerController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	playerHealth -= DamageAmount;

	//Tells GameMode to begin Respawn timer while dropping any Ball held and finally destroying Player Character.
	if (playerHealth <= 0) {
		GameModeRef->BeginPlayerRespawnProcess();
		if (bBallHeld) {
			PlayerCharacter->BallDropped();
			GameModeRef->SetBallHeld(false);
			bBallHeld = false;
		}
		PlayerCharacter->Destroy();
	}
	return DamageAmount;
}

void ACustomPlayerController::RecastPlayerCharacter()
{
	//Regrabs new PlayerCharacter after respawn.
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
}

void ACustomPlayerController::ResetHealth()
{
	//Resets Player health and ammo after death or round reset.
	playerHealth = playerHealthMax;
	gunClipAmmo = gunClipSize;
}
