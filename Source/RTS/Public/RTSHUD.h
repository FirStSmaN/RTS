// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/MainGameWidget.h"

#include "RTSHUD.generated.h"

class ARTSPlayerCharacter;
class ARTSSelectAndMoveCharacter;
UCLASS()
class RTS_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	void DrawHUD() override;
	
	ARTSPlayerCharacter* PlayerCharacter;
	FVector2D InitialMousePos;
	FVector2D EndMousePos;

	FVector2D GetMousePosition2D();

	bool bStartSelecting = false;
	bool bDoubleClicked = false;
	
	TArray <ARTSSelectAndMoveCharacter*> FoundedActors;

	public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY()
	UMainGameWidget* MainGameWidget;
	
};
