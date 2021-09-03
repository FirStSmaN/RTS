// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuController.h"

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	//SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	
}
