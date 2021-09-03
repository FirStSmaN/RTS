// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DiseaseStateWidget.h"



#include "RTSGameModeBase.h"
#include "RTSGameStateBase.h"
#include "Components/ProgressBar.h"

void UDiseaseStateWidget::UpdateOrganismPercent(float Percent)
{
	
	
	DiseaseStateProgressBar->SetPercent(Percent);

}
