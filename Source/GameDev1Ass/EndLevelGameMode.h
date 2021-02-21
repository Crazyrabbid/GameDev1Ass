// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV1ASS_API AEndLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void TimeUp();
	UPROPERTY()
		FTimerHandle GameOverTimer;
	UPROPERTY(EditAnywhere)
		float GameOverDuration = 30.0f;
};
