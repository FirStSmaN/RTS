#pragma once


#include "MyCoreTypes.generated.h"



DECLARE_MULTICAST_DELEGATE(FOnTitleTeamChanged)
DECLARE_MULTICAST_DELEGATE(FOnTemperatureChanged)



class MyCoreTypes
{
public:
	
};

UINTERFACE(MinimalAPI, Blueprintable)
class URTSSelectable : public UInterface
{
    GENERATED_BODY()
};

class IRTSSelectable
{    
    GENERATED_BODY()

public:
  
    virtual void SetSelection(bool Value);
 
};





UENUM(BlueprintType)
enum class FHeightName : uint8
{
	
    None = 0,
    Low,
    Middle,
	
	
};


UENUM(BlueprintType)
enum class FCellType : uint8
{
    Floor = 0,
    Ramp,
    Depth,
	
	
	
};

/*
class UMaterialInterface;
class ARTSSelectAndMoveCharacter;
USTRUCT(BlueprintType)
struct FTeamInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	int32 TeamID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	UMaterialInterface* TeamMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	FLinearColor TeamColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Team")
	float RespawnTimeModificator;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Spawn Params")
    TArray<TSubclassOf<ARTSSelectAndMoveCharacter>> Units;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Spawn Params")
	float RespawnTime;
	
	FTimerHandle RespawnTimerHandle;
	FOnRespawnTimerTick RespawnTimerTick;
};
*/
