// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSGameModeBase.h"
#include "RTSGameStateBase.h"
#include "Components/ActorComponent.h"
#include "RTSRespawnComponent.generated.h"

class ARTSSelectAndMoveCharacter;
class URTSTeamComponent;
class ARTGameStateBase;
class ARTSGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_API URTSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	URTSRespawnComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	APawn* GetUnitToRespawn(URTSTeamComponent* Team);
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Respawn Params")
	float RespawnTime;

	UPROPERTY()
	ARTSGameModeBase* GameMode;
	
	UPROPERTY()
	ARTSGameStateBase* GameState;
private:
	
	
	

		
};
