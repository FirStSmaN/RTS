// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/MoveToInRadiusTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Components/RTSAIController.h"
#include "NavigationSystem.h"
#include "Units/Components/RTSAIPerceptionComponent.h"
#include "RTSSelectAndMoveCharacter.h"

UMoveToInRadiusTask::UMoveToInRadiusTask()
{
	NodeName = "Move To In Radius";
}

EBTNodeResult::Type UMoveToInRadiusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	if(!Controller || !BlackBoard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;
	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if(!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(BlackBoard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if(!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
		
	}
	
	const auto Found =  NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if(!Found) return EBTNodeResult::Failed;
	BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
