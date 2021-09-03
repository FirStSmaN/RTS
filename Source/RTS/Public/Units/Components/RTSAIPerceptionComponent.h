// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "RTSAIPerceptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_API URTSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:	

	AActor* GetClosestEnemy() const;	
	AActor* GetClosestEnemyTitle() const;
};
