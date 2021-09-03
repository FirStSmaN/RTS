// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/Components/AIWeaponComponentComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/RTSAIController.h"
#include "Components/RTSAIHealthComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIWeaponComponent, All, All);

UAIWeaponComponentComponent::UAIWeaponComponentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIWeaponComponentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




void UAIWeaponComponentComponent::Attack(ARTSSelectAndMoveCharacter* EnemyCharacter)
{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(EnemyCharacter->Controller, EnemyCharacter);
    
    	UE_LOG(LogAIWeaponComponent, Display, TEXT("I am attacking!"))

		
}

bool UAIWeaponComponentComponent::CanAttack() const
{
	return true;
}


void UAIWeaponComponentComponent::StartAttack()
{
	UE_LOG(LogAIWeaponComponent, Display, TEXT("StartAttack"));

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopAttack();
		return;
	}
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	auto Enemy = Cast<ARTSSelectAndMoveCharacter>(HitResult.GetActor());
	if(!Enemy)
	{
		UE_LOG(LogAIWeaponComponent, Display, TEXT("Invalid Cast To Enemy"));
		return;
	}
	
	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo = HitResult;

	
	if(Enemy->GetTeam() == Cast<ARTSSelectAndMoveCharacter>(GetOwner())->GetTeam()) return;
	Enemy->TakeDamage(BaseDamage, PointDamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1, 0, 1);
	UE_LOG(LogAIWeaponComponent, Display, TEXT("Enemy HP: %f"), Enemy->GetHealthComponent()->GetHealth());
}


void UAIWeaponComponentComponent::StopAttack()
{
	UE_LOG(LogAIWeaponComponent, Display, TEXT("StopAttack"));
}

void UAIWeaponComponentComponent::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	auto OwnerActor = Cast<ARTSSelectAndMoveCharacter>(GetOwner());
	

	if (!GetWorld() || !OwnerActor || !OwnerActor->GetTeam())return;
	FCollisionQueryParams CollisionParams;

	
	CollisionParams.AddIgnoredActors(OwnerActor->GetTeam()->ActorUnits);
	
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = false;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Pawn, CollisionParams);

}

bool UAIWeaponComponentComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	auto Controller = Cast<ARTSAIController>(GetOwner()->GetInstigatorController());
	if(!Controller) return false;
	
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);


	TraceStart = ViewLocation;
	
	const FVector ShootDiraction =ViewRotation.Vector() ;
	TraceEnd = TraceStart + ShootDiraction * AttackDistance;
	return true;

}
