// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/RTSSelectAndMoveCharacter.h"
#include "RTSDiseaseCharacter.generated.h"

class URTSTeamComponent;
UCLASS()
class RTS_API ARTSDiseaseCharacter : public ARTSSelectAndMoveCharacter
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;


};
