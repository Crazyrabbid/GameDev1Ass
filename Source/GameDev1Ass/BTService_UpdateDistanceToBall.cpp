// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateDistanceToBall.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Math/Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdateDistanceToBall::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Ensures function is only ran in a level with a Ball.
	if (GetWorld()->GetName() == (TEXT("ArenaLevel")) || GetWorld()->GetName() == (TEXT("DevMap"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		//Calculates Enemy's distance to Ball through the square root of a dot product.
		if (GameModeRef->GetBallHeld() == false) {
			AAIController* EnemyAIController = OwnerComp.GetAIOwner();
			AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
			ABall* BallPawn = GameModeRef->inPlayBall;
			float Distance = sqrt(FVector::DotProduct(AIActor->GetActorLocation(), BallPawn->GetActorLocation()));

			//If distance is below threshold, Enemy picks up Ball.
			if (Distance < 100.0f) {
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
			}
			else {
				OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
			}
		}
	}
}

