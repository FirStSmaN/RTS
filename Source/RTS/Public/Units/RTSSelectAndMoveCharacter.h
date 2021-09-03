// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCoreTypes.h"

#include "RTSSelectAndMoveCharacter.generated.h"

class UAIWeaponComponentComponent;
class URTSTeamComponent;
class URTSRespawnComponent;
class URTSAIHealthComponent;
class UMaterialInterface;
class UPaperSpriteComponent;
class UBehaviorTree;
class UMaterialInterface;
class UDecalComponent;
class UWidgetComponent;

UCLASS(Blueprintable)
class ARTSSelectAndMoveCharacter : public ACharacter, public IRTSSelectable
{
	GENERATED_BODY()

public:
	ARTSSelectAndMoveCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	virtual void SetSelection(bool Value) override;
	virtual void Select();
	virtual void DisSelect();
	virtual void SetTeam(URTSTeamComponent* ValueTeamComponent);
	
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	
	UAIWeaponComponentComponent* GetWeaponComponent()const	{return WeaponComponent;}
	URTSAIHealthComponent* GetHealthComponent()const	{return HealthComponent;}
	
	URTSTeamComponent* GetTeam();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

private:


	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	URTSAIHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UMaterialInterface* DecalOnDeathMaterial;
	
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPaperSpriteComponent* MinimapSpriteComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URTSTeamComponent* TeamComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAIWeaponComponentComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthBarWidgetComponent;
	

	virtual void OnDeath();
	virtual void OnHealthChanged(float Health, float HealthDelta);
};

