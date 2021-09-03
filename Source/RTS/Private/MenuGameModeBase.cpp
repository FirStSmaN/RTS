// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameModeBase.h"
#include "Menu/MenuController.h"
#include "Menu/MenuHUD.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMenuController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}
