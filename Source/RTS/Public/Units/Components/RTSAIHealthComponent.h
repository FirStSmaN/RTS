// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSAIHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_API URTSAIHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSAIHealthComponent();
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyEqual(Health, 0.0f) ? true : false; }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const {return Health / MaxHealth;}

	float GetHealth() const { return Health; }
	

	
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetHealth(float NewHealth);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;

	float Health = 0.0f;

	



	
	
private:
	UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser );

	UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser );

	void ApplyDamage(float Damage, AController* InstigatedBy);

	UFUNCTION()
	void ReportDamageEvent(float Damage, AController* InstigatedBy);
		
};
