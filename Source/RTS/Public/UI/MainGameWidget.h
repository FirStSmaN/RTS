// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "MainGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UMainGameWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	void UpdateOrganismTitlesPercent();

	protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* OrganismPercentProgressBar;
	
};
