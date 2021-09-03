// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCoreTypes.h"
#include "RTSTeamComponent.generated.h"



class ABaseTitle;
class ARTSSelectAndMoveCharacter;
class UMaterialInterface;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_API URTSTeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSTeamComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	int32 TeamID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	UMaterialInterface* TeamMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	FLinearColor TeamColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	float RespawnTimeModificator;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Spawn Params")
	TArray<TSubclassOf<ARTSSelectAndMoveCharacter>> AvalibleUnits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Spawn Params")
	float RespawnTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Titles")
	TArray<ABaseTitle*> Titles;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Unit Spawn Params")
	TArray<AActor*> ActorUnits;

	
	
	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRespawnTimerTick, URTSTeamComponent*, InTeamComponent);

	FTimerDelegate RespawnDelegate;
	FOnRespawnTimerTick RespawnTimerTick;
	FTimerHandle RespawnTimerHandle;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	

		
};
