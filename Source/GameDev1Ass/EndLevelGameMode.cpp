// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "EndLevelGameMode.h"

void AEndLevelGameMode::BeginPlay() {
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(GameOverTimer, this, &AEndLevelGameMode::TimeUp, GameOverDuration, false);
}

void AEndLevelGameMode::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("TimeUpCalled"));
	if (GetWorld()->GetTimerManager().TimerExists(GameOverTimer)) GetWorld()->GetTimerManager().ClearTimer(GameOverTimer);
	UGameplayStatics::OpenLevel(GetWorld(), "ArenaLevel");
}