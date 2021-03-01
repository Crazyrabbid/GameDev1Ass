// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateBallPosition.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdateBallPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Ensures function only works if within levels that contain a Ball.
	if (GetWorld()->GetName() == (TEXT("ArenaLevel")) || GetWorld()->GetName() == (TEXT("DevMap"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		ABall* BallPawn = GameModeRef->inPlayBall;

		//Updates Ball position to ensure Eneemy keep following if within lineOfSight.
		if (BallPawn && GameModeRef->inPlayBall != nullptr) {
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), BallPawn->GetActorLocation());
		}
		else {
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
}
