// Fill out your copyright notice in the Description page of Project Settings.


#include "Titles/CustomMap.h"
#include "Titles/BaseTitle.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyCustomMap, All, All);
// Sets default values
ACustomMap::ACustomMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
}

// Called when the game starts or when spawned
void ACustomMap::BeginPlay()
{
	Super::BeginPlay();
	
	const auto TitleOwner = this;
	if(!GetWorld()) return;
	for(int32 ItY = 0; ItY < TitlesInRow; ItY++)
	{
		for(int32 ItX = 0; ItX < TitlesInRow; ItX++)
		{

			int32 CurrentIndex = ((TitlesInRow * ItY) + ItX);
			ABaseTitle* Title;

			Title = GetWorld()->SpawnActor<ABaseTitle>(FlatTitle);
			
			/*int32 Rand = FMath::RoundToInt(FMath::FRandRange(0.0, 0.6)) ;
			if(Rand == 0)
			{
				
				
			}else
			{
			Title = GetWorld()->SpawnActor<ABaseTitle>(RampTitle);
			
			}*/
			
			
			
			if(Title)
			{
				Title->SetOwner(TitleOwner);
				Title->AttachToActor(TitleOwner, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
				Titles.Add(Title);

				FVector Center;
				float Height = TitleRadius * FMath::Sin(PI/3);
				if (ItY % 2 == 0)																						//четные клетки
					{
					Center = FVector(1.5f * TitleRadius * ItY,2 * Height * ItX , 0);
					
					
					}
				else																										//нечетные клетки
					{
					Center = FVector(1.5f * TitleRadius * ItY,(2 * Height * ItX) + Height , 0);
					}
				Title->SetActorLocation(TitleOwner->GetActorLocation() + Center, false, nullptr, ETeleportType::None);
				//Title->TitleInfo.HeightName = FHeightName::None;
				
			}
			
            	
		}
	}


	
	/*Titles.Empty();
	HeightMap.Empty();

	GeneretaHeightMap();
	
	const auto TitleOwner = this;
	if(!GetWorld()) return;
	for(int32 ItY = 0; ItY < TitlesInRow; ItY++)
	{
		for(int32 ItX = 0; ItX < TitlesInRow; ItX++)
		{

			int32 CurrentIndex = ((TitlesInRow * ItY) + ItX);
			ABaseTitle* Title;

			Title = GetWorld()->SpawnActor<ABaseTitle>(FlatTitle);
			
			/*int32 Rand = FMath::RoundToInt(FMath::FRandRange(0.0, 0.6)) ;
			if(Rand == 0)
			{
				
				
			}else
			{
				 Title = GetWorld()->SpawnActor<ABaseTitle>(RampTitle);
			
			}#1#
			
			
			
			if(Title)
			{
				Title->SetOwner(TitleOwner);
                Title->AttachToActor(TitleOwner, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
				Titles.Add(Title);

				FVector Center;
				float Height = TitleRadius * FMath::Sin(PI/3);
				if (ItY % 2 == 0)																						//четные клетки
					{
					Center = FVector(1.5f * TitleRadius * ItY,2 * Height * ItX , HeightMap[CurrentIndex]);
					
					
					}
				else																										//нечетные клетки
					{
					Center = FVector(1.5f * TitleRadius * ItY,(2 * Height * ItX) + Height , HeightMap[CurrentIndex]);
					}
				Title->SetActorLocation(TitleOwner->GetActorLocation() + Center, false, nullptr, ETeleportType::None);
				Title->TitleInfo.HeightName = HeightMapNames[CurrentIndex];
				
			}
			
            	
		}
	}
	
	Flats.Empty();
	Flat.Empty();

	for(int32 i = 0; i < Titles.Num(); i++)
	{
		for(int32 j = 0; j < Flats.Num(); j++)
		{
			if(!Flat.Contains(i) && !Flats[j].Flat.Contains(i))
            		{
            			Flat.Add(i);         		
                        
            			FindNeighbours(i);
            			
                        
            		}
		}
		
		
	}
	FFlatInfo TempFlatInfo;
	TempFlatInfo.Flat = Flat;
	Flats.Add(TempFlatInfo);
	Flat.Empty();

	
	/*Flat.Empty();
	Flat.Add(0);
    FindNeighbours(0);
	for(int32 i = 0; i < Flat.Num(); i++)
	{
		UE_LOG(LogTemp, Display, TEXT("Flat Index Added: %i"), Flat[i] );
	}#1#

    UE_LOG(LogTemp, Display, TEXT("Flats.Num: %i"),  Flats.Num() );
	for(int32 i = 0; i < Flats.Num(); i++)
	{
		for(int32 j = 0; j < Flats[i].Flat.Num(); j++)
		{
				UE_LOG(LogTemp, Display, TEXT("Flats Indexes Added:  %i, %i"), j,  Flats[i].Flat[j] );
		}
	
				
	
	}*/
}

// Called every frame
void ACustomMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomMap::GeneretaHeightMap()
{
	for (int32 indexY = 0; indexY < TitlesInRow; indexY++)
	{
		for (int32 indexX = 0; indexX < TitlesInRow; indexX++)
		{
			/*auto LocalRandom = FMath::RandRange(0,1);
			if(LocalRandom == 0)
			{
			HeightsMap.Add(-100.0f);
			}
			if(LocalRandom == 1)
			{
			HeightsMap.Add(0.0f);
			}	*/
			const int32 CurrentIndex = (TitlesInRow * indexY) + indexX;
			
			HeightProperties.Add(FHeightName::Low, 0);
			HeightProperties.Add(FHeightName::Middle, 100);
			HeightProperties.Add(FHeightName::None, -100);
			const FHeightName RandomName = GetRandomHeightName();
			
			HeightMap.Add(*HeightProperties.Find(RandomName));
			HeightMapNames.Add(RandomName);
		}
	}	
}

FHeightName ACustomMap::GetRandomHeightName()
{
	int32 Randomint = FMath::RandRange(0, 2);
	
	return static_cast<FHeightName>(Randomint);
}

void ACustomMap::FindNeighbours(int32 CurrentTitle)
{
	int32 FirstTitleIndex = CurrentTitle;
	//if(!FirstTitleIndex) return;

	const float Lenght = 600.0f;
	
	
	
	
	TArray<int32> Neighbours;

	if((FirstTitleIndex + 1 >= 0) && (FirstTitleIndex + 1 < TitlesInRow * TitlesInRow))									// правая
	{
		if((Titles[FirstTitleIndex + 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add(FirstTitleIndex + 1) ;
	}
	
	if((FirstTitleIndex - 1 >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))									//левая 
	{
		if((Titles[FirstTitleIndex - 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex - 1);
	}
	
	if((FirstTitleIndex + TitlesInRow >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))						// правая верхняя
	{
		if((Titles[FirstTitleIndex + TitlesInRow]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() <Lenght)
		Neighbours.Add( FirstTitleIndex + TitlesInRow);
	}
	
	if((FirstTitleIndex + TitlesInRow + 1 >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))					// левая верхняя
	{
		if((Titles[FirstTitleIndex + TitlesInRow + 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex  + TitlesInRow + 1);
	}
	
	if((FirstTitleIndex - TitlesInRow >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))						// левая нижняя
	{
		if((Titles[FirstTitleIndex - TitlesInRow]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex - TitlesInRow);
	}
	
	if((FirstTitleIndex - TitlesInRow - 1 >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))					// правая нижняя
	{
		if((Titles[FirstTitleIndex - TitlesInRow - 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex - TitlesInRow - 1);
	}
	
	if((FirstTitleIndex - TitlesInRow + 1 >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))
	{
		if((Titles[FirstTitleIndex - TitlesInRow + 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex - TitlesInRow + 1);
	}
	
	if((FirstTitleIndex + TitlesInRow - 1 >= 0) && (FirstTitleIndex - 1 < TitlesInRow * TitlesInRow))
	{
		if((Titles[FirstTitleIndex + TitlesInRow - 1]->GetActorLocation() - Titles[FirstTitleIndex]->GetActorLocation()).Size() < Lenght)
		Neighbours.Add( FirstTitleIndex + TitlesInRow - 1);
	}
	
	
	
	/*for(int32 i = 0; i < Neighbours.Num(); i++)																			
	{
		UE_LOG(LogTemp, Display, TEXT("Neighbour Index Added: %i"), Neighbours[i] );
		if(Titles[Neighbours[i]]->TitleInfo.HeightName == Titles[FirstTitleIndex]->TitleInfo.HeightName)
		{
			
			//if(!Flat.Find(Neighbours[i]))
			
			UE_LOG(LogTemp, Display, TEXT("Current Height Name : %i %s;Neighbour Height Name : %i %s"), FirstTitleIndex,  *UEnum::GetValueAsString(Titles[FirstTitleIndex]->TitleInfo.HeightName), Neighbours[i], *UEnum::GetValueAsString(Titles[Neighbours[i]]->TitleInfo.HeightName)  )
			if(!Flat.Contains(Neighbours[i]))
			{
				Flat.Add(Neighbours[i]);
                FindNeighbours(Neighbours[i]);
			}
			
		}
	}*/

	
	
}
