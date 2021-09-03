// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RTSSelectAndMoveCharacter.h"
#include "Components/ActorComponent.h"
#include "AIWeaponComponentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_API UAIWeaponComponentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIWeaponComponentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float AttackDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage = 0;
	


		
public:	
	

	UFUNCTION()
	void Attack(ARTSSelectAndMoveCharacter* EnemyCharacter);

	UFUNCTION()
	virtual void StartAttack();

	UFUNCTION()
	virtual void StopAttack();

	
	UFUNCTION()
	bool CanAttack() const;		

	UFUNCTION()
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	UFUNCTION()
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
};
