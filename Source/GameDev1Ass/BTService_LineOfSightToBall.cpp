// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LineOfSightToBall.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LineOfSightToBall::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Ensures function only works if within levels that contain a Ball.
	if (GetWorld()->GetName() == (TEXT("ArenaLevel")) || GetWorld()->GetName() == (TEXT("DevMap"))) {

		//Grabs reference to current Ball within level.
		AAIController* EnemyAIController = OwnerComp.GetAIOwner();
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		ABall* BallPawn = GameModeRef->inPlayBall;

		//Checks Enemy can see Ball so Enemy will chase it, pick it up and attempt to score.
		if (EnemyAIController->LineOfSightTo(BallPawn)) {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		}
		else {
			EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
}
