// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToInRadiusTask.generated.h"
 
UCLASS()
class RTS_API UMoveToInRadiusTask : public UBTTaskNode
{
	GENERATED_BODY()
	public:
	UMoveToInRadiusTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI")
	float Radius = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI")
	bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI", meta = (EditCondition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;
	

};
