// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Components/RTSRespawnComponent.h"

#include <Actor.h>
#include "Units/Components/RTSTeamComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Units/RTSSelectAndMoveCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogRespawnComponent, All, All);

// Sets default values for this component's properties
URTSRespawnComponent::URTSRespawnComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void URTSRespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());

	if(!GetWorld() || !GetWorld()->GetGameState()) return;
	GameState = Cast<ARTSGameStateBase>(GetWorld()->GetGameState());

	
	
}


// Called every frame
void URTSRespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


APawn* URTSRespawnComponent::GetUnitToRespawn(URTSTeamComponent* Team)
{
	if(!Team || Team->AvalibleUnits.Num() <= 0) return nullptr;
	int32 Random = FMath::RandRange(0, Team->AvalibleUnits.Num()-1);


	
	auto ActorToSpawn = Team->AvalibleUnits[Random];
	auto SpawnParams = FActorSpawnParameters();
	
	FRotator Rotation = FRotator(0,0,0);
	
	if(!GetWorld() || !ActorToSpawn || !GetOwner() )
	{
		UE_LOG(LogRespawnComponent, Warning, TEXT("Cant Spawn Unit: !GetWorld() || !ActorToSpawn || !GetOwner() "));
		return nullptr;
	}
	//auto SpawnedUnit = Cast<ARTSSelectAndMoveCharacter>(GetWorld()->SpawnActor(ActorToSpawn->StaticClass()));
	const auto SpawnedPawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), ActorToSpawn, nullptr, GetOwner()->GetActorLocation(), Rotation, true, nullptr) ;


	
	auto SpawnedRTSUnit = Cast<ARTSSelectAndMoveCharacter>(SpawnedPawn);
	
	if(!SpawnedPawn || !SpawnedRTSUnit) return nullptr; 
	SpawnedRTSUnit->SetTeam(Team);
	return SpawnedRTSUnit;		
}
