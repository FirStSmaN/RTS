// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSSelectAndMoveCharacter.h"
#include "BasePlayerController.generated.h"

class ARTSHUD;

UCLASS()
class RTS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	ABasePlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY()
	int32 ScreenSizeX;
	UPROPERTY()
	int32 ScreenSizeY;
	
	UFUNCTION()
    FVector GetPanDirection();

	protected:

	
	
	ARTSHUD* HUDptr;
	
	UPROPERTY()
	float Marigin = 10;

	TArray<ARTSSelectAndMoveCharacter*> SelectedActors;
	private:
	
	UFUNCTION()
	void BeginSelect();
	
	UFUNCTION()
	void EndSelect();
	
	UFUNCTION()
	void MoveTo();

	UFUNCTION()
	void Attack();
	
	UFUNCTION()
	void OnDoubleClick();

	UFUNCTION()
	bool CanManipulate(APawn* OtherPawn);

	
	
	

};
