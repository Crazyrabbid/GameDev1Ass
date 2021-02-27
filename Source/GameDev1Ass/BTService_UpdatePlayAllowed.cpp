// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayAllowed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_UpdatePlayAllowed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (GetWorld()->GetName() == (TEXT("ArenaLevel"))|| GetWorld()->GetName() == (TEXT("DevMap"))) {
		GameModeRef = Cast<AGameDev1AssGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), GameModeRef->GetPlayAllowed());
	}
}