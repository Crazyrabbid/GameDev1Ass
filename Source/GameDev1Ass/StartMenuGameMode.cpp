// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AStartMenuGameMode::BeginPlay() {
	//Spawns Menu UI and plays background music.
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(GetWorld(), GameBackgroundMusic, BackgroundMusicVolume, 1.0f, 0.0f);
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}