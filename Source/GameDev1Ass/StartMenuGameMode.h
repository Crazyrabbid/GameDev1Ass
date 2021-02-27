// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API AStartMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainMenuClass;
	UPROPERTY()
		UUserWidget* MainMenuCount;
	UPROPERTY(EditAnywhere) float BackgroundMusicVolume = 1.0f;
	UPROPERTY(EditAnywhere) USoundBase* GameBackgroundMusic;
};
