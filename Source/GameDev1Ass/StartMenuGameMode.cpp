// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuGameMode.h"
#include "Blueprint/UserWidget.h"

void AStartMenuGameMode::BeginPlay() {
	Super::BeginPlay();
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}