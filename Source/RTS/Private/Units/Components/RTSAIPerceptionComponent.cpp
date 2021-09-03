// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Components/RTSAIPerceptionComponent.h"


#include "RTSSelectAndMoveCharacter.h"
#include "Components/RTSAIHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Titles/BaseTitle.h"
#include "Units/Components/RTSAIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogPerceptionComponent, All, All);


AActor* URTSAIPerceptionComponent::GetClosestEnemy()const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if(PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);	
		if(PercieveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;
	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	
	for(const auto PercieveActor: PercieveActors)
	{
		const auto HealthComponent = Cast<URTSAIHealthComponent>(PercieveActor->GetComponentByClass(URTSAIHealthComponent::StaticClass()));
		
		const auto PercievePawn = Cast<ARTSSelectAndMoveCharacter>(PercieveActor);
		if(!PercievePawn) continue;
		const auto AreEnemies = Cast<ARTSSelectAndMoveCharacter>(Controller->GetPawn())->GetTeam() != PercievePawn->GetTeam();
		
	
		if(HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = ((PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size());
			if(CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}

		}
		
		
	}
	return BestPawn;	
}


AActor* URTSAIPerceptionComponent::GetClosestEnemyTitle() const
{
		
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if(PercieveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
	
		if(PercieveActors.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller)
	{
		UE_LOG(LogPerceptionComponent, Display, TEXT("No Owner Pawn"));
		return nullptr;
	}
	const auto Pawn = Controller->GetPawn();
	if(!Pawn)
	{
		UE_LOG(LogPerceptionComponent, Display, TEXT("No Owner Pawn"));
		return nullptr;
	}
	
	TArray<ABaseTitle*> TitleActors;
	
	
	for(int32 i = 0; i < PercieveActors.Num(); i++)
	{
		
		UE_LOG(LogPerceptionComponent, Display, TEXT("Percieved Actor.Num: %i"), PercieveActors.Num());
		
		auto Title = Cast<ABaseTitle>(PercieveActors[i]);
		if(Title)
		{
			UE_LOG(LogPerceptionComponent, Display, TEXT("Cast Succeeded"));
			TitleActors.Add(Title);
		} 
		
	}

	

    AActor* BestActor = nullptr;
    float Distance = FLT_MAX;
	if(TitleActors.Num() == 0)
	{
		UE_LOG(LogPerceptionComponent, Display, TEXT("Percieved titles num = 0"));
		return nullptr;
	}
	for(int32 i = 0; i < TitleActors.Num(); i++)
	{

		if(Distance > Pawn->GetDistanceTo(TitleActors[i]))
		{
			UE_LOG(LogPerceptionComponent, Display, TEXT("Distance: %f"), Pawn->GetDistanceTo(TitleActors[i]) );
			BestActor = TitleActors[i];
		}
	}

	if(!BestActor) return nullptr;
	

	return BestActor;
}