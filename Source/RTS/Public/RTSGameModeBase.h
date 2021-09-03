// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "Titles/BaseTitle.h"
#include "Units/Components/RTSTeamComponent.h"
#include "RTSGameModeBase.generated.h"

class ABaseTitle;

UCLASS()
class RTS_API ARTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


	public:

	ARTSGameModeBase();
	

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	URTSTeamComponent* OrganismTeamComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	URTSTeamComponent* DiseaseTeamComponent;
	
	UPROPERTY()
    TArray<ABaseTitle*> Titles;

	URTSTeamComponent* GetOppositeTeam(URTSTeamComponent* SelfTeam);

	virtual void BeginPlay() override;

	private:
	UFUNCTION()
	void MakeDisease();
	
	UFUNCTION()
	ABaseTitle* GetRandomTitle(URTSTeamComponent* TeamComponent);

	UFUNCTION()
	void OnRespawnTimerTick(URTSTeamComponent* TeamComponent);

	
	protected:
	
};
