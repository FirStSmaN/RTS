// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Components/RTSAIController.h"
#include "RTSSelectAndMoveCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Components/RTSAIPerceptionComponent.h"

ARTSAIController::ARTSAIController()
{
	RTSAIPerceptionComponent = CreateDefaultSubobject<URTSAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*RTSAIPerceptionComponent);
	
}

void ARTSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto RTSCharacter = Cast<ARTSSelectAndMoveCharacter>(InPawn);
	if(RTSCharacter)
	{
		RunBehaviorTree(RTSCharacter->BehaviorTreeAsset);
	}
}

void ARTSAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}


AActor* ARTSAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent())
	{		
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}