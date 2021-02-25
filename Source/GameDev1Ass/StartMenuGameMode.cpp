// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "StartMenuGameMode.h"

void AStartMenuGameMode::BeginPlay() {
	Super::BeginPlay();
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}