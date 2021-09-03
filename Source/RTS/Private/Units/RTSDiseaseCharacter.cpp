// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/RTSDiseaseCharacter.h"
#include "RTSGameModeBase.h"
#include "Units/Components/RTSTeamComponent.h"
#include "MyCoreTypes.h"


void ARTSDiseaseCharacter::BeginPlay()
{
	
	auto GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return; 
	
	SetTeam(GameMode->DiseaseTeamComponent);
	GetTeam()->ActorUnits.Add(this);
	
	Super::BeginPlay();
	
}




