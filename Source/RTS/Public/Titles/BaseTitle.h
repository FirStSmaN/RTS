// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCoreTypes.h"
#include "RTSSelectAndMoveCharacter.h"
#include "Components/SphereComponent.h"
#include "Units/Components/RTSTeamComponent.h"
#include "BaseTitle.generated.h"


USTRUCT(BlueprintType)
struct FTitleInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Title Info" )
	int32 TitleIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Title Info" )
	FCellType CellType;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Title Info" )
	FHeightName HeightName;
};

UCLASS()
class RTS_API ABaseTitle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTitle();
	
	UFUNCTION()
	virtual void ConquerTitle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	UFUNCTION()	
    void ChangeTeam(URTSTeamComponent* ValueTeamComponent);

	UFUNCTION()
	URTSTeamComponent* GetTeam(){return TeamComponent;}

	UFUNCTION(BlueprintCallable)
	URTSRespawnComponent* GetRespawnComponent(){return RespawnComponent;}

	UFUNCTION()
	bool IsOppositeTeam(URTSTeamComponent* OtherTeamComponent) const;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	

	FOnTitleTeamChanged OnTitleTeamChanged;
public:	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Title Params")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Title Params")
	USphereComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URTSRespawnComponent* RespawnComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URTSTeamComponent* TeamComponent;


	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Spawn Params")
	bool bCanSpawnUnits = true;
};
