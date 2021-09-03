// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameStateBase.h"
#include "UI/DiseaseStateWidget.h"

#include "RTSGameModeBase.h"
#include "RTSHUD.h"
#include "UI/MainGameWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogRTSGameState, All, All);
void ARTSGameStateBase::TitleCheck()
{
	

	
	if(!GetWorld()) return;
		const auto GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GameMode) return;
	if(GameMode->OrganismTeamComponent == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("DISEASE WINS!"))
	}

	if(GameMode->DiseaseTeamComponent == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Organism WINS!"))
	}

	UE_LOG(LogRTSGameState, Display, TEXT("TitleChecked"))
	auto RTSHUD = Cast<ARTSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(!RTSHUD) UE_LOG(LogRTSGameState, Display, TEXT("NO RTSHUD"));
	
	const auto MainWidget = (RTSHUD->MainGameWidget);
	
	if(!MainWidget) UE_LOG(LogRTSGameState, Display, TEXT("NO MAINWIDGET"));
	if(MainWidget) MainWidget->UpdateOrganismTitlesPercent();
	
}
