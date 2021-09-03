// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiseaseStateWidget.generated.h"

class UProgressBar;
UCLASS()
class RTS_API UDiseaseStateWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	void UpdateOrganismPercent(float Percent);
	
	protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* DiseaseStateProgressBar;
	
};
