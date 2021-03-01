// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"

void AMainMenuController::BeginPlay() {
	Super::BeginPlay();

	//Ensures player can interact with Main Menu.
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}