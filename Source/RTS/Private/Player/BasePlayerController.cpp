// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "RTSHUD.h"
#include "MyCoreTypes.h"
#include "DrawDebugHelpers.h"
#include "RTSPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Components/AIWeaponComponentComponent.h"
#include "Units/RTSSelectAndMoveCharacter.h"
#include "UI/MainGameWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"


DEFINE_LOG_CATEGORY_STATIC(LogRTSPlayerController, All, All);

ABasePlayerController::ABasePlayerController()
{
	
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;


	HUDptr = Cast<ARTSHUD>(GetHUD());
	if(!HUDptr)
	{
		UE_LOG(LogRTSPlayerController, Warning, TEXT("NoHUD!"));
		return;
	} 
	GetViewportSize(ScreenSizeX, ScreenSizeY);

	
	
	
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed,this , &ABasePlayerController::BeginSelect);
	InputComponent->BindAction("LeftMouseClick", IE_Released,this , &ABasePlayerController::EndSelect);

	InputComponent->BindAction("RightMouseClick", IE_Pressed,this , &ABasePlayerController::MoveTo);
	InputComponent->BindAction("RightMouseClick", IE_Pressed,this , &ABasePlayerController::Attack);
	InputComponent->BindAction("MouseLeftClick", IE_DoubleClick, this, &ABasePlayerController::OnDoubleClick);
}

void ABasePlayerController::BeginSelect()
{
	
	if(!HUDptr)
	{
		UE_LOG(LogRTSPlayerController, Warning, TEXT("NoHUD!"));
		return;
	} 
	UE_LOG(LogRTSPlayerController, Display, TEXT("BeginSelect"))
	HUDptr->InitialMousePos = HUDptr->GetMousePosition2D();
	HUDptr->bStartSelecting = true;
}

void ABasePlayerController::EndSelect()
{
	if(!HUDptr)
	{
		UE_LOG(LogRTSPlayerController, Warning, TEXT("NoHUD!"));
		return;
	} 

	if(SelectedActors.Num() > 0)
	{
		for(auto SelectedActor : SelectedActors) // int32 i = 0; i < SelectedActors.Num(); i++)
			{
			
			if(!CanManipulate(SelectedActor)) continue;
			SelectedActor->DisSelect();
			
		}
	}
	
	HUDptr->bStartSelecting = false;
	SelectedActors = HUDptr->FoundedActors;
	
	if(SelectedActors.Num() > 0)
	{
		for(auto SelectedActor : SelectedActors) // int32 i = 0; i < SelectedActors.Num(); i++)
		{
			if(!SelectedActor->IsValidLowLevel()) SelectedActors.Remove(SelectedActor);
			if(!CanManipulate(SelectedActor)) continue;
			SelectedActor->Select();
			
		}
	}
	
}

void ABasePlayerController::MoveTo()
{
	UE_LOG(LogRTSPlayerController, Display, TEXT("Amount of selected bots: %i"), SelectedActors.Num());
	if(SelectedActors.Num() > 0)
	{
		
		
		for(auto SelectedActor : SelectedActors)
		{
			if(!SelectedActor->IsValidLowLevel()) SelectedActors.Remove(SelectedActor);
			if(!CanManipulate(SelectedActor)) continue;

			const auto BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(SelectedActor);
			if(!BlackBoard) continue;
				
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false,Hit );
			FVector MoveLocation = Hit.Location + FVector(1/2 * 100, FMath::RandRange(-50, 50),  0);
		
			BlackBoard->SetValueAsVector(FName("AimLocation"), MoveLocation);

			DrawDebugSphere(GetWorld(), BlackBoard->GetValueAsVector(FName("AimLocation")), 50, 6, FColor::Red, false, 5, 0, 3);
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActor->GetController(), MoveLocation);
			
		}
	}
}

FVector ABasePlayerController::GetPanDirection()
{
	float MouseX = 0;
	float MouseY = 0;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	GetMousePosition(MouseX,MouseY);

	if((MouseX <= Marigin) && MouseX >= 0)
	{
		CamDirectionY = -1;	
	}

	if(MouseY <= Marigin && MouseY >= 0)
	{
		CamDirectionX = 1;
	}
	
	if(MouseX >= ScreenSizeX - Marigin && MouseX <= ScreenSizeX)
	{
		CamDirectionY = 1;
	}
	

	if(MouseY >= ScreenSizeY - Marigin && MouseY <= ScreenSizeY )
	{
		CamDirectionX = -1;
	}
	return FVector(CamDirectionX, CamDirectionY, 0);
}

void ABasePlayerController::OnDoubleClick()
{
	UE_LOG(LogRTSPlayerController, Display, TEXT("DoubleClick"))				// TODO это нужно перенести в класс худа
	
	/*if(!GetWorld()) return;
	HUDptr->bStartSelecting = true;
	

	FHitResult HitResult;

	FVector MouseWorldLocation;
	FVector MouseWorldDiraction;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	
	DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDiraction);
	
	GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldLocation, MouseWorldLocation + (MouseWorldDiraction * 12000.0f), ECollisionChannel::ECC_Pawn, CollisionQueryParams);
	UE_LOG(LogRTSPlayerController, Display, TEXT("HitResult.bBlockingHit: %i"), HitResult.bBlockingHit);
	
	auto BotCharacter = Cast<ARTSOrganismCharacter>(HitResult.GetActor());
	if(!BotCharacter)
	{
		UE_LOG(LogRTSPlayerController, Display, TEXT("UNABLE TO CAST!"));
		return;
	}

	TArray<ARTSOrganismCharacter*> OrganismCharacters;
	

	
	HUDptr->GetActorsInSelectionRectangle<ARTSOrganismCharacter>(FVector2D(0.0, 0.0), FVector2D(ScreenSizeX, ScreenSizeY), OrganismCharacters , false, false);
	UE_LOG(LogTemp, Display, TEXT("DoubleClicked Actors.Num(): %i"), OrganismCharacters.Num());
	if(OrganismCharacters.Num() > 0)
	for(int32 i = 0; i < OrganismCharacters.Num(); i++)
	{
		SelectedActors.Add(OrganismCharacters[i]);
		OrganismCharacters[i]->Select();
	}
	 EndSelect();
	 */
}

void ABasePlayerController::Attack()
{
	FHitResult HitResult;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false,HitResult);

	const auto BotPawn = Cast<APawn>(HitResult.Actor);
	if(!BotPawn) return;	

	const auto BotCharacter = Cast<ARTSSelectAndMoveCharacter>(BotPawn);
	if(!BotCharacter) return;

	 UE_LOG(LogRTSPlayerController, Display, TEXT("Right Click On BotPawn"))
	
	if(SelectedActors.Num() > 0)
	{
		
		
		for(auto SelectedActor : SelectedActors)
		{
			if(!SelectedActor->IsValidLowLevel()) SelectedActors.Remove(SelectedActor);
			if(!CanManipulate(SelectedActor)) continue;
			SelectedActor->GetWeaponComponent()->StartAttack();			
		}
	}
}

bool ABasePlayerController::CanManipulate(APawn* OtherPawn)
{
	if(!OtherPawn->IsValidLowLevel() || !OtherPawn || !OtherPawn->GetController() || Cast<ARTSSelectAndMoveCharacter>(OtherPawn)->GetTeam() != Cast<ARTSPlayerCharacter>(GetPawn())->GetTeam()) return false;

	return true;
}