// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"


#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

	public:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MenuWidgetClass;
};
