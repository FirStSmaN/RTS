// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSAIController.generated.h"

class URTSAIPerceptionComponent;
UCLASS()
class RTS_API ARTSAIController : public AAIController
{
	GENERATED_BODY()

	public:
	ARTSAIController();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	URTSAIPerceptionComponent* RTSAIPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "AI")
	FName  FocusOnKeyName = "EnemyActor";
		
	void virtual OnPossess(APawn* InPawn) override;
	virtual  void Tick(float DeltaTime) override;


	
	private:
	AActor* GetFocusOnActor() const;
};
