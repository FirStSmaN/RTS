// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Servises/BTService_FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Components/RTSAIPerceptionComponent.h"
#include "Units/Components/RTSAIController.h"
#include "Units/Components/AIWeaponComponentComponent.h"

UBTService_FireService::UBTService_FireService()
{
	NodeName = "Fire Service";
}

void UBTService_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Controller = Cast<ARTSAIController>(OwnerComp.GetAIOwner());
	auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	auto Character = Cast<ARTSSelectAndMoveCharacter>(Controller->GetPawn());

	auto HasAim = BlackBoardComponent && BlackBoardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	
	if(Controller && Character && BlackBoardComponent)
	{
		const auto AiWeaponComponent = Cast<UAIWeaponComponentComponent>(Character->FindComponentByClass(UAIWeaponComponentComponent::StaticClass()));
		if(AiWeaponComponent)
		{
			HasAim ? AiWeaponComponent->StartAttack() : AiWeaponComponent->StopAttack();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}