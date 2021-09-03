// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class URTSAIHealthComponent;
class UProgressBar;
UCLASS()
class RTS_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	void SetHealthPercent(float Percent);
	
	protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentVisibilityThreshold = 0.8;

	
};
