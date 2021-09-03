// Fill out your copyright notice in the Description page of Project Settings.


#include "Titles/BaseTitle.h"


#include "RTSGameModeBase.h"
#include "RTSGameStateBase.h"
#include "RTSSelectAndMoveCharacter.h"
#include "Units/Components/RTSRespawnComponent.h"
#include "Units/Components/RTSTeamComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseTitle, All, All);

// Sets default values
ABaseTitle::ABaseTitle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

	Trigger = CreateDefaultSubobject<USphereComponent>("Trigger");
	Trigger->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

	RespawnComponent = CreateDefaultSubobject<URTSRespawnComponent>("RespawnComponent");
	TeamComponent = CreateDefaultSubobject<URTSTeamComponent>("TeamComponent");
	RootComponent = MeshComponent;


	Trigger->SetSphereRadius(200.0f, true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseTitle::ConquerTitle);


	//Trigger->OnComponentBeginOverlap.AddUniqueDynamic()
}

// Called when the game starts or when spawned
void ABaseTitle::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return; // гейммод
	const auto GameMode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)


		if (!GetWorld() || !GetWorld()->GetGameState()) return; // геймстейт
	const auto GameState = Cast<ARTSGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
		GameState->OrganismTitlesCount++;
	GameState->TitleCount++;

	ChangeTeam(GameMode->OrganismTeamComponent);
	GameMode->Titles.Add(this);
	OnTitleTeamChanged.AddUFunction(GameState, "TitleCheck");
}



/*void ABaseTitle::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

		
		
}*/

void ABaseTitle::ConquerTitle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	TArray<AActor*> OverLappedActors;
	GetOverlappingActors(OverLappedActors, ARTSSelectAndMoveCharacter::StaticClass());
	for (auto OverLappedActor : OverLappedActors)
	{
		const auto ARTSOverlappedChar = Cast<ARTSSelectAndMoveCharacter>(OverLappedActor);
		if (ARTSOverlappedChar)
			if (ARTSOverlappedChar->GetTeam() == GetTeam()) return;
	}


	auto BaseUnit = Cast<ARTSSelectAndMoveCharacter>(OtherActor);
	if (!BaseUnit || !BaseUnit->GetTeam() || !BaseUnit->GetTeam()->TeamMaterial) return;

	UMaterialInterface* TeamMaterial = BaseUnit->GetTeam()->TeamMaterial;

	if (TeamComponent != BaseUnit->GetTeam())
	{
		ChangeTeam(BaseUnit->GetTeam());
	}
}

void ABaseTitle::ChangeTeam(URTSTeamComponent* ValueTeamComponent)
{
	if (!TeamComponent || !ValueTeamComponent) return;
	if (TeamComponent != ValueTeamComponent)
	{
		if (TeamComponent->Titles.Contains(this))
		{
			TeamComponent->Titles.Remove(this);
		}

		TeamComponent = ValueTeamComponent;

		if (!TeamComponent->Titles.Contains(this))
		{
			TeamComponent->Titles.Add(this);
		}

		const auto TeamMaterial = TeamComponent->TeamMaterial;

		if (MeshComponent)
			for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++) // смена материала
			{
				if (MeshComponent->GetMaterial(i) != TeamMaterial && TeamMaterial)
					MeshComponent->SetMaterial(i, TeamMaterial);
			}
	}
	

	OnTitleTeamChanged.Broadcast();
}

/*
void ABaseTitle::SpawnUnit(TSubclassOf<ARTSSelectAndMoveCharacter> Unit)
{
	
}*/

bool ABaseTitle::IsOppositeTeam(URTSTeamComponent* OtherTeamComponent) const
{
	if (TeamComponent != OtherTeamComponent) return true;

	return false;
}
