// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainGameWidget.h"
#include "RTSGameModeBase.h"

void UMainGameWidget::UpdateOrganismTitlesPercent()
{
	const auto RTSGameMode =Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	
	
	float Percent = (float) RTSGameMode->OrganismTeamComponent->Titles.Num() / RTSGameMode->Titles.Num() ;
	if(OrganismPercentProgressBar)
	OrganismPercentProgressBar->SetPercent(Percent);
}