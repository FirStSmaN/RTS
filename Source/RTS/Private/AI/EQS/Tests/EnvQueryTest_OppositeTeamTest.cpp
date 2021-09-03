// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/Tests/EnvQueryTest_OppositeTeamTest.h"
#include "Titles/BaseTitle.h"
#include "RTSGameModeBase.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"


UEnvQueryTest_OppositeTeamTest::UEnvQueryTest_OppositeTeamTest(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_OppositeTeamTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	auto Gamemode = Cast<ARTSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!Gamemode) return;
	
	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto Title = Cast<ABaseTitle>(ItemActor);
		if(!Title) continue;

		if(Title->IsOppositeTeam(Gamemode->DiseaseTeamComponent))
		{
			It.SetScore(TestPurpose, FilterType, true, true);
		}else
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
		
	
	}
}