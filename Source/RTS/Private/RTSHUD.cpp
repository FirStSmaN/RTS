// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "BasePlayerController.h"
#include "RTSPlayerCharacter.h"
#include "RTSSelectAndMoveCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainGameWidget.h"
#include "Components/RTSAIHealthComponent.h"



void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();
	if(GetOwningPlayerController() && GetOwningPlayerController()->GetPawn())
	PlayerCharacter = Cast<ARTSPlayerCharacter>(GetOwningPlayerController()->GetPawn());

	MainGameWidget = CreateWidget<UMainGameWidget>(GetWorld(), MainGameWidgetClass);
	if(MainGameWidget)	MainGameWidget->AddToPlayerScreen();
	
}




FVector2D ARTSHUD::GetMousePosition2D()
{
	float X;
	float Y;
	GetOwningPlayerController()->GetMousePosition(X, Y);
	
	return FVector2D(X, Y);
}

void ARTSHUD::DrawHUD()
{
	
	if(!PlayerCharacter) return;
	
	if(bStartSelecting)
	{
		if(FoundedActors.Num() > 0)
		{
			for(int32 i = 0; i < FoundedActors.Num(); i++)
			{
				if(FoundedActors[i]->IsValidLowLevel() && FoundedActors[i]->GetTeam() ==  PlayerCharacter->GetTeam())
				{
					FoundedActors[i]->DisSelect();
					
				}
			}
		}
		FoundedActors.Empty();
		EndMousePos = GetMousePosition2D();
		DrawRect(FLinearColor(0,0,10, 0.15f), InitialMousePos.X, InitialMousePos.Y, EndMousePos.X - InitialMousePos.X, EndMousePos.Y - InitialMousePos.Y);
		GetActorsInSelectionRectangle<ARTSSelectAndMoveCharacter>(InitialMousePos, EndMousePos,FoundedActors, false, false);
	}

	/*if(bDoubleClicked)
	{
		if(FoundedActors.Num() > 0)
		{
			for(int32 i = 0; i < FoundedActors.Num(); i++)
			{
				FoundedActors[i]->DisSelect();
			}
		}
		FoundedActors.Empty();

		auto Controller = Cast<ABasePlayerController>(GetOwningPlayerController());
		if(!Controller) return;
		GetActorsInSelectionRectangle<ARTSSelectAndMoveCharacter>(FVector2D(0.0, 0.0), FVector2D(Controller->ScreenSizeX, Controller->ScreenSizeY),FoundedActors, false, false);
	}*/
	
	if(FoundedActors.Num() > 0)
	{
		for(int32 i = 0; i < FoundedActors.Num(); i++)
		{
			if(FoundedActors[i]->IsValidLowLevel() && FoundedActors[i]->GetTeam() ==  PlayerCharacter->GetTeam())
			{
				FoundedActors[i]->Select();
			}
			
		}
	}
	
}

