// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCoreTypes.h"
#include "CustomMap.generated.h"
class ABaseTitle;

USTRUCT() 
struct FFlatInfo 
{
	
	GENERATED_USTRUCT_BODY();

	TArray<int32> Flat;
	
	
};

UCLASS()
class RTS_API ACustomMap : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	ACustomMap();
	virtual void Tick(float DeltaTime) override;

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Title Params", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 TitlesInRow = 3;

	TArray<ABaseTitle*> Titles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title Types")
	TSubclassOf<ABaseTitle> FlatTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title Types")
	TSubclassOf<ABaseTitle> RampTitle;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title Params", meta = (ClampMin = "0", ClampMax = "10000"))
	float TitleRadius = 100.0f;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Title Params")
	TMap<FHeightName, int32> HeightProperties ;

	TArray<int32> HeightMap;
	TArray<FHeightName> HeightMapNames;
	int32 UpperHeight = 100;

	private:
	TArray<FFlatInfo> Flats;
	TArray<int32> Flat;
	//TArray<int32,TArray<int32> > Flats;
	void GeneretaHeightMap();
	FHeightName GetRandomHeightName();
	void FindNeighbours(int32);
	
	
};