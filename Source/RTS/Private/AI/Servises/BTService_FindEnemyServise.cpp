// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Servises/BTService_FindEnemyServise.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Components/RTSAIPerceptionComponent.h"
#include "Units/Components/RTSAIController.h"


UBTService_FindEnemyServise::UBTService_FindEnemyServise()
{
	NodeName = "Find Enemy";
}

void UBTService_FindEnemyServise::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	if(BlackBoardComponent)
	{
		auto Controller = Cast<ARTSAIController>(OwnerComp.GetAIOwner());
		auto PerceptionComponent = Cast<URTSAIPerceptionComponent>(Controller->GetAIPerceptionComponent());

		if(Controller && PerceptionComponent)
		{
			BlackBoardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}