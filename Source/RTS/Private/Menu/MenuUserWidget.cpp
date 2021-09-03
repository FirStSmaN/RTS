// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnGameStart);
	}
}

void UMenuUserWidget::OnGameStart()
{
	const FName StartLevelName = "HugeLevel";
	UGameplayStatics::OpenLevel(GetWorld(), StartLevelName);
}

