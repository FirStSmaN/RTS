// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyCoreTypes.h"

#include "RTSGameStateBase.generated.h"

class UUserWidget;

UCLASS()
class RTS_API ARTSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	
	public:

	UFUNCTION()
	void TitleCheck();

	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Organism Settings", meta = (ClampMin = "30", ClampMax = "41"))
	float Temperature = 36.6;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Organism Settings")
	float MinTemperature = 30;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Organism Settings")
	float MaxTemperature = 41;

	UPROPERTY(BlueprintReadWrite)
	int32 OrganismTitlesCount = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 DiseaseTitlesCount = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 TitleCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UUserWidget* OrganismStateWidgetComponent;

};
