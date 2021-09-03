// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/RTSSelectAndMoveCharacter.h"
#include "RTSOrganismCharacter.generated.h"

class URTSTeamComponent;
UCLASS()
class RTS_API ARTSOrganismCharacter : public ARTSSelectAndMoveCharacter
{
	GENERATED_BODY()


	public:
	virtual void BeginPlay() override;

};
