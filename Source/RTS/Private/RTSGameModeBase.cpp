// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RTSDiseaseCharacter.h"
#include "Units/Components/RTSRespawnComponent.h"
#include "Units/Components/RTSTeamComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

ARTSGameModeBase::ARTSGameModeBase()
{
	OrganismTeamComponent = CreateDefaultSubobject<URTSTeamComponent>("OrganismTeamComponent"); // Cast<URTSTeamComponent>(AddComponent(OrganismTeamComponent->GetFName(), false, FTransform(FVector(0.0,0.0,0.0)), GetWorld(),false ));
                            	
	DiseaseTeamComponent = CreateDefaultSubobject<URTSTeamComponent>("DiseaseTeamComponent"); //Cast<URTSTeamComponent>(AddComponent(DiseaseTeamComponent->GetFName(), false, FTransform(FVector(0.0,0.0,0.0)), GetWorld(),false ));
	
}

void ARTSGameModeBase::BeginPlay()
{
	
	Super::BeginPlay();
	MakeDisease();

	OrganismTeamComponent->RespawnDelegate.BindUObject(this, &ARTSGameModeBase::OnRespawnTimerTick, OrganismTeamComponent);
	DiseaseTeamComponent->RespawnDelegate.BindUObject(this, &ARTSGameModeBase::OnRespawnTimerTick, DiseaseTeamComponent);

	
	GetWorld()->GetTimerManager().SetTimer(OrganismTeamComponent->RespawnTimerHandle, OrganismTeamComponent->RespawnDelegate,  OrganismTeamComponent->RespawnTime * OrganismTeamComponent->RespawnTimeModificator, false, -1);
	GetWorld()->GetTimerManager().SetTimer(DiseaseTeamComponent->RespawnTimerHandle, DiseaseTeamComponent->RespawnDelegate, DiseaseTeamComponent->RespawnTime * DiseaseTeamComponent->RespawnTimeModificator, false,-1);


	//GetWorldTimerManager().SetTimer(DiseaseTeamComponent->RespawnTimerHandle ,TempDiseaseRespawnDelegate,DiseaseTeamComponent->RespawnTime, true);
	
}

void ARTSGameModeBase::MakeDisease()
{
	int32 Random = FMath::RandRange(0, Titles.Num()-1);

	const auto DiseaseTeam = DiseaseTeamComponent;

	
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	if(!IsValid(Titles[Random])) return;
	  
	auto TeamMaterial = DiseaseTeam->TeamMaterial;
	
	Titles[Random]->ChangeTeam(DiseaseTeam);
    			
	for(int32 i = 0; i < Titles[Random]->MeshComponent->GetNumMaterials(); i++)												// смена материала
	{
		if(Titles[Random]->MeshComponent->GetMaterial(i) != TeamMaterial)
			Titles[Random]->MeshComponent->SetMaterial(i,TeamMaterial);
	}


	GetRandomTitle(DiseaseTeamComponent)->GetRespawnComponent()->GetUnitToRespawn(DiseaseTeam);
}

void ARTSGameModeBase::OnRespawnTimerTick(URTSTeamComponent* TeamComponent)
{
	if(!GetWorld()) return;
	auto Title = GetRandomTitle(TeamComponent); //Cast<ABaseTitle>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseTitle::StaticClass()));
	if(!Title) return;
	Title->GetRespawnComponent()->GetUnitToRespawn(TeamComponent);

	if(TeamComponent == DiseaseTeamComponent)
	{
		if(TeamComponent->Titles.Num() > 0)
		{
			float TitlesPercent = (float)TeamComponent->Titles.Num()/Titles.Num();
			TeamComponent->RespawnTimeModificator = 1 - TitlesPercent;
		
			UE_LOG(LogGameModeBase, Display, TEXT("DiseaseTeam Respawn Modificator: %f"), DiseaseTeamComponent->RespawnTimeModificator);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(TeamComponent->RespawnTimerHandle, TeamComponent->RespawnDelegate, TeamComponent->RespawnTime * TeamComponent->RespawnTimeModificator, false, -1);
	
}

ABaseTitle* ARTSGameModeBase::GetRandomTitle(URTSTeamComponent* TeamComponent)
{
	UE_LOG(LogGameModeBase, Display, TEXT("TeamComponent unit spawned: %s"), *TeamComponent->GetName());
	int32 Random = FMath::RandRange(0, TeamComponent->Titles.Num()-1);
	if(TeamComponent->Titles.Num() > 0 && IsValid(TeamComponent->Titles[Random]))
	return TeamComponent->Titles[Random];
	
	return nullptr;
}

URTSTeamComponent* ARTSGameModeBase::GetOppositeTeam(URTSTeamComponent* SelfTeam)
{
	if(SelfTeam == OrganismTeamComponent)
	{
		return DiseaseTeamComponent;
	}
	if(SelfTeam == DiseaseTeamComponent)
	{
		return OrganismTeamComponent;
	}

	return nullptr;
}