// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) ? ESlateVisibility::Hidden : ESlateVisibility::Visible;

	HealthBar->SetVisibility(HealthBarVisibility);
	HealthBar->SetPercent(Percent);


}
