// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

class UButton;
UCLASS()
class RTS_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	virtual void NativeOnInitialized() override;

	protected:
	UFUNCTION()
	void OnGameStart();
};
