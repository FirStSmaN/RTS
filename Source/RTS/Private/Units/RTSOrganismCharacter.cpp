// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/RTSOrganismCharacter.h"
#include "Units/Components/RTSTeamComponent.h"
#include "RTSGameModeBase.h"

void ARTSOrganismCharacter::BeginPlay()
{
	
	auto GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return; 
		
	SetTeam(GameMode->OrganismTeamComponent);
	GetTeam()->ActorUnits.Add(this);
	
	Super::BeginPlay();
}

