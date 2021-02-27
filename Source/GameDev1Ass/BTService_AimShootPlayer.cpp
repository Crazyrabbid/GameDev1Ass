// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AimShootPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

void UBTService_AimShootPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	EnemyAIController->SetFocus(PlayerPawn);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSoundEffect, AIActor->GetActorLocation(), ShotSoundVolume, 1.0f, 0.0f);

	FVector end = AIActor->GetActorLocation() + AIActor->GetActorForwardVector() * castRange;

	FHitResult Hit;
	FCollisionQueryParams lineTraceParams;

	lineTraceParams.AddIgnoredActor(AIActor);
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, AIActor->GetActorLocation(), end, ECC_Pawn, lineTraceParams);
	if (bDidHit && Hit.GetActor() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());
		if (Hit.GetActor()->FindComponentByClass(UCharacterMovementComponent::StaticClass())) {

		}
		else {
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
			RootComp->AddImpulse(AIActor->GetActorForwardVector() * impulseForce * RootComp->GetMass());
		}
		UGameplayStatics::ApplyDamage(Hit.GetActor(), gunBaseDamage, EnemyAIController, AIActor, UDamageType::StaticClass());
	}
}